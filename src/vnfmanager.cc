
#include "vnfmanager.h"
#include "../messages/nfvMessages_m.h"
#include "../messages/servicemsg_m.h"
#include "../messages/deploymentplan_m.h"
Define_Module(Vnfmanager);

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


}

void Vnfmanager::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        handleSelfMessage(msg);
        return;
    }
    if (auto *plan = dynamic_cast<VnfDeploymentPlan *>(msg)) {
        handleDeploymentPlan(plan);
    }

    if (auto resp = dynamic_cast<VnfDeploymentResponse*>(msg)) {
           handleVnfDeploymentResponse(resp);
       }


}
void Vnfmanager::handleDeploymentPlan(VnfDeploymentPlan* plan) {
    int targetNfviNodeGateIndex = plan->getNfviNodeId();
    int enterpriseId = plan->getEnterpriseId();
    EV << "VNFManager: Received deployment plan for enterprise " << enterpriseId
       << " targeting NFVINode[" << targetNfviNodeGateIndex << "]\n";

    std::vector<int> serverVnfIPs;
    std::map<std::string, int> assignedIps; // name → ip
    int expected = plan->getBlueprintsArraySize();

    expectedDeploymentsPerEnterprise[enterpriseId] = expected;
    receivedDeploymentsPerEnterprise[enterpriseId] = 0;

    EV << "VNFManager: Deployment plan for enterprise " << enterpriseId
       << " expects " << expected << " VNFs.\n";

    // First pass: assign IPs
    for (int i = 0; i < expected; ++i) {
        const auto& bp = plan->getBlueprints(i);
        assignedIps[bp.getVnfName()] = nextVnfIp++;
    }

    // Second pass: send deployment requests
    for (int i = 0; i < expected; ++i) {
        const auto& bp = plan->getBlueprints(i);

        VnfDeploymentRequest *req = new VnfDeploymentRequest("VnfDeploymentRequest");
        req->setVnfName(bp.getVnfName());
        req->setVnfType(bp.getVnfType());
        req->setNfviNodeId(plan->getNfviNodeId());
        req->setCpuRequest(bp.getCpu());
        req->setRequestId(enterpriseId);
        //setting requestid to enterprise id for now
        req->setMemoryRequest(bp.getMemory());
        req->setBandwidthRequest(bp.getBandwidth());

        int ip = assignedIps[bp.getVnfName()];
        req->setVnfIpAddress(ip);

        // Collect server IPs for LB config
        if (bp.getVnfType() == VNF_TYPE_SERVER) {
            serverVnfIPs.push_back(ip);
        }

        // Handle LoadBalancer backend server IPs
        if (bp.getVnfType() == VNF_TYPE_LOADBALANCER) {
            req->setBackendServerIpsArraySize(serverVnfIPs.size());
            for (size_t j = 0; j < serverVnfIPs.size(); ++j) {
                req->setBackendServerIps(j, serverVnfIPs[j]);
            }
        }

        EV << "VNFManager: Deploying " << bp.getVnfName() << " with IP " << ip << "\n";
        send(req, "nfviNodeGateOut", targetNfviNodeGateIndex);
    }
    delete plan;
}
void Vnfmanager::handleVnfDeploymentResponse(VnfDeploymentResponse *resp) {
    if (resp->getSuccess()) {
        EV << "Deployment succeeded for " << resp->getVnfName() << "\n";

    } else {
        EV_WARN << "Deployment failed for " << resp->getVnfName() << ": " << resp->getInfoMessage() << "\n";
    }
    int enterpriseId = resp->getRequestId();
    receivedDeploymentsPerEnterprise[enterpriseId]++;

    EV << "Received VNF deployment response for enterprise " << enterpriseId
       << ". Total received: " << receivedDeploymentsPerEnterprise[enterpriseId]
       << "/" << expectedDeploymentsPerEnterprise[enterpriseId] << "\n";

    if (receivedDeploymentsPerEnterprise[enterpriseId] == expectedDeploymentsPerEnterprise[enterpriseId]) {
        EV << "All VNFs deployed for enterprise " << enterpriseId << ". Sending ack and wiring trigger.\n";
        // Send response to NFVO
        ServiceChainAck *ack=new ServiceChainAck();
        ack->setEnterpriseId(resp->getRequestId());
        ack->setSuccess(true);
        ack->setMessageinfo("Successfully deployed service chain");
        ack->setNfviNodeId(resp->getNfviNodeId());
        ack->setAvailableCPU(resp->getAvailableCPU());
        ack->setAvailableMemory(resp->getAvailableMemory());
        ack->setAvailableBandwidth(resp->getAvailableBandwidth());


        send(ack, "nfvoGateOut");
        EV<<"Sent response to nfvoGateOut"<<endl;
        // Trigger wiring
        cMessage* wiringTrigger = new cMessage("TriggerWiring");
        wiringTrigger->addPar("enterpriseId") = enterpriseId;
        send(wiringTrigger, "nfviNodeGateOut", resp->getNfviNodeId());  // or choose target node appropriately
        EV<<"Sent the wiring trigger"<<endl;
    } else {
        delete resp;  // Only delete if not forwarded
    }




}

void Vnfmanager::handleSelfMessage(cMessage *msg) {
   EV<<"VNF Manager self message"<<endl;
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
