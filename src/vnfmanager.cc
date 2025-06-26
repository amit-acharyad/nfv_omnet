//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include "vnfmanager.h"
#include "nfvMessages_m.h"
Define_Module(Vnfmanager);
// Self-message kind for triggering deployment
enum VnfManagerMessageKinds {
    TRIGGER_DEPLOYMENT = 1000,
};
void Vnfmanager::initialize()
{
    nfvoGate = gate("nfvoGateOut");
    // Ensure nfviNodeGate is treated as a vector if it's a vector gate in NED
    numNfviNodes = gateSize("nfviNodeGateOut"); // Get actual size of connected gates
    nextVnfIp = 100; // Starting IP for VNFs (e.g., 100, 101, 102...)

    // Store NFVI node IDs for future reference (optional, could just use gate index)
    for (int i = 0; i < numNfviNodes; ++i) {
        nfviNodeIds.push_back(i); // Assuming gate index maps to NFVINode index for now
    }

    // --- Define the Service Chain Blueprint ---
    // This is where you specify WHICH VNFs to deploy and in what conceptual order.
    // We will deploy: Firewall -> LoadBalancer -> 3 WebServers

    // 1. WebServerVNFs (deploy first so their IPs are known for LoadBalancer)
    serviceChainBlueprint.push_back({VNF_TYPE_SERVER, "Server1", 1000, 512, 100});
    serviceChainBlueprint.push_back({VNF_TYPE_SERVER, "Server2", 1000, 512, 100});
    serviceChainBlueprint.push_back({VNF_TYPE_SERVER, "Server3", 1000, 512, 100});

    // 2. LoadBalancer
    serviceChainBlueprint.push_back({VNF_TYPE_LOADBALANCER, "LoadBalancer1", 500, 256, 50});

    // 3. Firewall (entry point of the service chain)
    serviceChainBlueprint.push_back({VNF_TYPE_FIREWALL, "Firewall1", 700, 256, 70});


    // Trigger the deployment process after a short delay to allow all modules to initialize
    scheduleAt(simTime() + 1.0, new cMessage("TriggerDeployment", TRIGGER_DEPLOYMENT));
}

void Vnfmanager::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        handleSelfMessage(msg);
        return;
    }

    // Check if the message is a VnfDeploymentResponse
    VnfDeploymentResponse* response = dynamic_cast<VnfDeploymentResponse*>(msg);
    if (response) {
        EV << "VnfManager: Received VNF Deployment Response for " << response->getVnfName()
           << ". Success: " << (response->getSuccess() ? "true" : "false")
           << ", Deployed IP: " << response->getDeployedVnfIp() << endl;

        if (response->getSuccess()) {
            DeployedVnfInfo info;
            info.name = response->getVnfName();
            info.ipAddress = response->getDeployedVnfIp();
            // Need to figure out VNF type from original request or name,
            // for simplicity, let's derive it or store it during request
            // For now, type and nfviNodeId will be filled when we iterate through blueprint
            deployedVnfs[info.name] = info;

            // If a WebServerVNF was deployed, add its IP to our list for the LoadBalancer
            // This is a simple way; for more complex scenarios, match by type/name
            if (info.name.find("Server") != std::string::npos) { // Crude check for WebServerVNF
                serverVnfIPs.push_back(info.ipAddress);
                EV << "VnfManager: WebServerVNF IP " << info.ipAddress << " added to list." << endl;
            }

            // TODO: If this was the last expected response for a service chain,
            // then inform the PacketSwitch about the service entry point (Firewall IP).
            // This will be the next big step after getting deployment working.

        } else {
            EV_WARN << "VnfManager: VNF Deployment failed for " << response->getVnfName() << ": " << response->getInfoMessage() << endl;
        }
        delete response;
    } else {
        EV << "VnfManager: Received unhandled message: " << msg->getName() << endl;
        delete msg;
    }
}

void Vnfmanager::handleSelfMessage(cMessage *msg) {
    if (msg->getKind() == TRIGGER_DEPLOYMENT) {
        EV << "VnfManager: Triggering service chain deployment." << endl;
        deployServiceChain();
    }
    delete msg; // Delete the self-message
}

void Vnfmanager::deployServiceChain() {
    // This logic assumes we deploy all VNFs to nfviNode[0] for simplicity first.
    // In a real scenario, NFVO would decide placement.
    int targetNfviNodeGateIndex = 0; // Assuming nfviNode[0] is connected to gate 0

    for (const auto& config : serviceChainBlueprint) {
        VnfDeploymentRequest *req = new VnfDeploymentRequest("VnfDeploymentRequest");
        req->setVnfName(config.name.c_str());
        req->setVnfType(config.type);
        req->setCpuRequest(config.cpu);
        req->setMemoryRequest(config.mem);
        req->setBandwidthRequest(config.bw);

        // Assign unique IP
        req->setVnfIpAddress(nextVnfIp++);
        EV << "VnfManager: Preparing deployment for " << config.name << " with IP " << req->getVnfIpAddress() << endl;

        // === Handle WebServer ===
        if (config.type == VNF_TYPE_SERVER) {
            serverVnfIPs.push_back(req->getVnfIpAddress()); // <<<<<< ADD THIS
        }

        // === Handle LoadBalancer ===
        if (config.type == VNF_TYPE_LOADBALANCER) {
            if (serverVnfIPs.empty()) {
                EV_ERROR << "VnfManager: Attempting to deploy LoadBalancer before WebServers' IPs are known!" << endl;
            }
            req->setBackendServerIpsArraySize(serverVnfIPs.size());
            for (size_t i = 0; i < serverVnfIPs.size(); ++i) {
                req->setBackendServerIps(i, serverVnfIPs[i]);
            }
            EV << "VnfManager: LoadBalancer requested with " << serverVnfIPs.size() << " backend IPs." << endl;
        }

        send(req, "nfviNodeGateOut", targetNfviNodeGateIndex);
        EV << "VnfManager: Sent deployment request for " << config.name << " to NFVINode[" << targetNfviNodeGateIndex << "]" << endl;
    }

}

void Vnfmanager::finish()
{
    EV << "VnfManager: Deployed VNFs count: " << deployedVnfs.size() << endl;
    // Optional: report statistics or print final deployed VNF list
}
