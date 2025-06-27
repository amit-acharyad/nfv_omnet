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

#include "nfvinode.h"
#include "nfvMessages_m.h"
#include "firewall.h"
#include "loadbalancer.h"
#include "server.h"
#include <cstring>
#include "packet_m.h"
#include <queue>


Define_Module(Nfvinode);

void Nfvinode::initialize()
{
    EV << "NFVINode[" << getId() << "]: Initializing." << endl;
    dataPlaneIp = par("dataPlaneIp").intValue();
    totalCpuCapacity = par("cpuCapacity").doubleValue(); // Get as double
    totalMemoryCapacity = par("memoryCapacity").doubleValue(); // Get as double
    totalNetworkBandwidth = par("networkBandwidth").doubleValue(); // Get as double

    availableCpu = totalCpuCapacity;
    availableMemory = totalMemoryCapacity;
    availableBandwidth = totalNetworkBandwidth;
    internalConnectionsDone=false;
    vnfIdCounter = 0; // Initialize VNF ID counter

    EV << "NFVINode " << getId() << " Initialized with capacities: CPU=" << totalCpuCapacity
       << " MEM=" << totalMemoryCapacity << " BW=" << totalNetworkBandwidth << endl;
    EV << "NFVINode[" << getId() << "]: My Data Plane IP: " << dataPlaneIp << endl;

    EV<<"Registering port"<<endl;
    int myIp = par("dataPlaneIp").intValue();  // or store it in a member variable

        Packet *reg = new Packet("Register");
        reg->setSourceAddress(myIp);
        reg->setIsRegistration(true);
        send(reg, "ethOut", 0);  // assuming 1 ethOut per node, index 0
}

void Nfvinode::handleMessage(cMessage *msg)
{
    // Check if it's a management message (VnfDeploymentRequest)
    VnfDeploymentRequest* vnfRequest = dynamic_cast<VnfDeploymentRequest*>(msg);
    if (vnfRequest) {
        handleVnfDeploymentRequest(vnfRequest);
        return;
    }

    // Check if it's a data plane packet
    Packet* packet = dynamic_cast<Packet*>(msg);
    if (packet) {
        if (!internalConnectionsDone) {
            EV << "NFVINode[" << getId() << "]: Buffering packet until wiring is ready.\n";
            bufferedPackets.push(packet);
            return;
        } else {
            EV << "Handling Packet from gate no " << packet->getArrivalGateId() << endl;
            handleDataPacket(packet, msg->getArrivalGate());
            return;
        }
    }


     if ( strcmp(msg->getName(), "TriggerServiceChainWiring") == 0) {
        EV << "NFVINode: Received wiring trigger.\n";
        wireInternalServiceChain(); // call the method we discussed earlier
        internalConnectionsDone=true;
        delete msg;
        while (!bufferedPackets.empty()) {
                Packet* p = bufferedPackets.front();
                bufferedPackets.pop();
                handleDataPacket(p, p->getArrivalGate());
            }
        return;
    }
     else {
         EV_WARN << "NFVINode[" << getId() << "]: Received unhandled message of type "
                 << msg->getClassName() << ": " << msg->getName() << endl;
         delete msg;
     }
}

void Nfvinode::handleVnfDeploymentRequest(VnfDeploymentRequest *req)
{
    EV << "NFVINode[" << getId() << "]: Received VNF Deployment Request for " << req->getVnfName()
       << " (Type: " << req->getVnfType() << ", IP: " << req->getVnfIpAddress() << ")" << endl;

    VnfDeploymentResponse *response = new VnfDeploymentResponse("VnfDeploymentResponse");
    response->setVnfName(req->getVnfName());
    response->setDeployedVnfIp(0); // Default to 0, set on success
    response->setRequestId(req->getRequestId());

    // Check resource availability
    if (req->getCpuRequest() > availableCpu ||
        req->getMemoryRequest() > availableMemory ||
        req->getBandwidthRequest() > availableBandwidth)
    {
        response->setSuccess(false);
        response->setInfoMessage("Insufficient resources");
        EV_WARN << "NFVINode[" << getId() << "]: Deployment failed for " << req->getVnfName()
                << ": Insufficient resources." << endl;
        send(response, "managementGateOut");
        delete req;
        return;
    }

    // Determine module type name string for creation
    const char* vnfTypeName = nullptr;
    switch (req->getVnfType()) {
        case VNF_TYPE_FIREWALL:
            vnfTypeName = "omnet_nfv.Firewall";
            break;
        case VNF_TYPE_LOADBALANCER:
            vnfTypeName = "omnet_nfv.Loadbalancer";
            break;
        case VNF_TYPE_SERVER:
            vnfTypeName = "omnet_nfv.Server";
            break;
        default:
            response->setSuccess(false);
            response->setInfoMessage("Unknown VNF type");
            EV_ERROR << "NFVINode[" << getId() << "]: Unknown VNF type requested: " << req->getVnfType() << endl;
            send(response, "managementGateOut");
            delete req;
            return;
    }

    // Check if there is room in vnf[] vector to deploy another VNF
    if (vnfIdCounter >= par("numVnfs").intValue()) {
        response->setSuccess(false);
        response->setInfoMessage("No capacity to deploy more VNFs");
        EV_WARN << "NFVINode[" << getId() << "]: Deployment failed for " << req->getVnfName()
                << ": Capacity full." << endl;
        send(response, "managementGateOut");
        delete req;
        return;
    }

    // Create module inside vnf[] vector at index vnfIdCounter
    int idx = vnfIdCounter++;
    cModuleType* vnfModuleType = cModuleType::get(vnfTypeName);
    cModule* vnfModule = vnfModuleType->create(req->getVnfName(), this);


    vnfModule->buildInside();

    // Set common parameters
    vnfModule->par("myIpAddress").setIntValue(req->getVnfIpAddress());

    // Set VNF-specific parameters
    if (req->getVnfType() == VNF_TYPE_FIREWALL) {
        vnfModule->par("loadBalancerVIP").setIntValue(req->getFirewallLbVip());
    }
    else if (req->getVnfType() == VNF_TYPE_LOADBALANCER) {
        // 1. Collect already deployed server IPs
        std::vector<int> backendServerIps;
        for (const auto& [ip, vnf] : deployedVnfsByIp) {
            if (vnf.type == VNF_TYPE_SERVER) {
                backendServerIps.push_back(ip);
            }
        }

        // 2. If no servers exist, skip LB deployment
        if (backendServerIps.empty()) {
            EV_WARN << "NFVINode[" << getId() << "]: No backend servers found. Skipping LoadBalancer deployment." << endl;
            delete req;
            return;  // Exit without deploying LB
        }
        // 3. Cast to Loadbalancer* and directly assign vector
            Loadbalancer* lb = check_and_cast<Loadbalancer*>(vnfModule);
            lb->setBackendServerIps(backendServerIps);
            EV << "NFVINode[" << getId() << "]: Initialized LoadBalancer with "
               << backendServerIps.size() << " backend servers.\n";
    }


    vnfModule->callInitialize();

    // Update resource accounting
    availableCpu -= req->getCpuRequest();
    availableMemory -= req->getMemoryRequest();
    availableBandwidth -= req->getBandwidthRequest();

    // Store deployed VNF info
    DeployedVnfModule deployedVnf;
    deployedVnf.name = req->getVnfName();
    deployedVnf.type = req->getVnfType();
    deployedVnf.ipAddress = req->getVnfIpAddress();
    deployedVnf.moduleRef = vnfModule;

    deployedVnfsByIp[deployedVnf.ipAddress] = deployedVnf;
    deployedVnfsByName[deployedVnf.name] = deployedVnf;

    // Send success response
    response->setSuccess(true);
    response->setInfoMessage("VNF deployed successfully");
    response->setDeployedVnfIp(req->getVnfIpAddress());

    EV << "NFVINode[" << getId() << "]: Successfully deployed " << req->getVnfName()
       << " with IP " << req->getVnfIpAddress() << ". Remaining Resources (CPU: " << availableCpu
       << ", Mem: " << availableMemory << ", BW: " << availableBandwidth << ")" << endl;

    send(response, "managementGateOut");
    delete req;
}


void Nfvinode::handleDataPacket(Packet *packet, cGate *arrivalGate)
{
    int destinationIp = packet->getDestinationAddress();

    if (arrivalGate->isName("ethIn")) {
        // Always forward incoming external packets to Firewall
        bool foundFirewall = false;
        for (const auto& [ip, vnf] : deployedVnfsByIp) {
            if (vnf.type == VNF_TYPE_FIREWALL) {
                send(packet, "internalOut");
                EV << "NFVINode[" << getId() << "]: Incoming packet forwarded to Firewall ("
                   << vnf.name << ") setting foundfirewall to true" << endl;
                foundFirewall=true;
                break;
            }
        }

        if(!foundFirewall){
            EV_WARN << "NFVINode[" << getId() << "]: No Firewall found. Dropping packet." << endl;
                    delete packet;
        }

    }

    else {
        // Packet is from an internal VNF
        cModule* sender = arrivalGate->getOwnerModule();
        int destIp = packet->getDestinationAddress();

        auto it = deployedVnfsByIp.find(destIp);
        if (it != deployedVnfsByIp.end()) {
            // Forward to next internal VNF
            send(packet, it->second.moduleRef->gate("in"));
            EV << "NFVINode[" << getId() << "]: Forwarded packet internally from "
               << sender->getName() << " to " << it->second.name << endl;
        } else {
            // Final hop: send packet out
            send(packet, "ethOut", 0);  // You can match destinationIp to gate index if needed
            EV << "NFVINode[" << getId() << "]: Packet sent to external network for IP: "
               << destIp << endl;
        }
    }
}



void Nfvinode::wireInternalServiceChain() {
    cModule* firewall = nullptr;
    cModule* loadBalancer = nullptr;
    std::vector<cModule*> servers;

    // Identify VNF types
    for (const auto& [name, vnf] : deployedVnfsByName) {
        switch (vnf.type) {
            case VNF_TYPE_FIREWALL:
                firewall = vnf.moduleRef;
                break;
            case VNF_TYPE_LOADBALANCER:
                loadBalancer = vnf.moduleRef;
                break;
            case VNF_TYPE_SERVER:
                servers.push_back(vnf.moduleRef);
                break;
            case VNF_TYPE_UNKNOWN:
                break;
        }
    }

    // Connect Firewall to LoadBalancer (if both exist)
    if (firewall && loadBalancer) {
        firewall->gate("outLB")->connectTo(loadBalancer->gate("in"));
        loadBalancer->gate("out")->connectTo(firewall->gate("inLB"));

       gate("internalOut") ->connectTo(firewall->gate("in"));
       firewall->gate("out")->connectTo(gate("internalIn"));
        EV << "NFVINode: Connected Firewall <--> LoadBalancer\n";
    }

    // Connect LoadBalancer to all Servers (if any)
    if (loadBalancer && !servers.empty()) {
        int serverIndex = 0;
        loadBalancer->setGateSize("outServer", servers.size());
         loadBalancer->setGateSize("inServer", servers.size());
        for (auto* server : servers) {
            loadBalancer->gate("outServer", serverIndex)->connectTo(server->gate("in"));
            server->gate("out")->connectTo(loadBalancer->gate("inServer",serverIndex));
            EV << "Connected LoadBalancer.outServer[" << serverIndex << "] -> "
               << server->getName() << ".in and server out to loadbalancer inserver\n";
            ++serverIndex;
        }
    }

    // You can add reverse connections if servers need to reply back
}



