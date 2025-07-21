#include "nfvo.h"
#include "../messages/servicemsg_m.h"
#include "../messages/deploymentplan_m.h"
#include "../messages/nfvMessages_m.h"
#include <string>

Define_Module(Nfvo);

void Nfvo::initialize() {
    int numNfviNodes=par("numNfviNodes");
    for(int i=0;i<numNfviNodes;i++){
        nfviNodeResources[i]={10000, 8192, 1000};
        nfviNodeIds.push_back(i);
    }
    EV<<"Resources of"<<numNfviNodes<<"Initialized"<<endl;
}

void Nfvo::handleMessage(cMessage *msg) {
    if (auto *req = dynamic_cast<ServiceChainRequest *>(msg)) {
        handleServiceChainRequest(req);
    }else if (auto *res = dynamic_cast<ServiceChainAck *>(msg)) {
        sendServiceChainAck(res);
    }
    else {
        EV << "NFVO received unknown message type\n";
        delete msg;
    }
}

void Nfvo::handleServiceChainRequest(ServiceChainRequest *req) {
    EV << "NFVO: Received service chain request from enterprise " << req->getEnterpriseId() << "\n";

    int enterpriseId = req->getEnterpriseId();
    std::string chainType = req->getChainType();
    int numServers = req->getDesiredServerCount();
    NfviAvailableResources needed=computeTotalResources(numServers);
    // For now, pick NFVINode 0 statically
    int nfviNodeId = -1;
    int totalNodes = nfviNodeIds.size();

    for (int i = 0; i < totalNodes; ++i) {
        // Round-robin index
        int index = (lastUsedNodeIndex + 1 + i) % totalNodes;
        int nodeId = nfviNodeIds[index];

        const auto& resources = nfviNodeResources[nodeId];

        if (resources.cpu >= needed.cpu &&
            resources.memory >= needed.memory &&
            resources.bandwidth >= needed.bandwidth) {
            nfviNodeId = nodeId;
            lastUsedNodeIndex = index; // update for next round
            break;
        }
    }

      if (nfviNodeId != -1) {
          sendDeploymentPlan(enterpriseId, nfviNodeId, chainType, numServers);
      } else {
          EV << "NFVO: No NFVI node with enough resources for request from enterprise " << enterpriseId << "\n";
          // optionally send rejection
      }

    delete req;
}

void Nfvo::sendDeploymentPlan(int enterpriseId, int nfviNodeId, const std::string& chainType, int numServers) {
    VnfDeploymentPlan *plan = new VnfDeploymentPlan("vnfDeploymentPlan");

    plan->setEnterpriseId(enterpriseId);
    plan->setNfviNodeId(nfviNodeId);

    std::vector<VnfBlueprint> blueprintList;

    // Add servers
    for (int i = 1; i <= numServers; ++i) {
        VnfBlueprint bp;
        std::string servername = "Server" + std::to_string(enterpriseId) + std::to_string(nfviNodeId)+std::to_string(i);
        bp.setVnfName(servername.c_str());
        bp.setVnfType(VNF_TYPE_SERVER); // VNF_TYPE_SERVER (define your own enums as needed)
        bp.setCpu(1000);
        bp.setMemory(512);
        bp.setBandwidth(100);
        blueprintList.push_back(bp);
    }

    // LoadBalancer
    VnfBlueprint lb;
    std::string lbname = "Loadbalancer" + std::to_string(enterpriseId) + std::to_string(nfviNodeId);
    lb.setVnfName(lbname.c_str());    lb.setVnfType(VNF_TYPE_LOADBALANCER); // VNF_TYPE_LOADBALANCER
    lb.setCpu(500);
    lb.setMemory(256);
    lb.setBandwidth(50);
    blueprintList.push_back(lb);

    // Firewall
    VnfBlueprint fw;
    std::string fwname = "Firewall" + std::to_string(enterpriseId) + std::to_string(nfviNodeId);
    fw.setVnfName(fwname.c_str());
    fw.setVnfType(VNF_TYPE_FIREWALL); // VNF_TYPE_FIREWALL
    fw.setCpu(700);
    fw.setMemory(256);
    fw.setBandwidth(70);
    blueprintList.push_back(fw);

    // Set blueprint array
    plan->setBlueprintsArraySize(blueprintList.size());
    for (int i = 0; i < blueprintList.size(); ++i) {
        plan->setBlueprints(i, blueprintList[i]);
    }

    send(plan, "vnfMgrGateOut");
}
NfviAvailableResources Nfvo:: computeTotalResources(int numServers) {
    // Static resource costs per VNF
    const double serverCpu = 1000, serverMem = 512, serverBw = 100;
    const double lbCpu = 500, lbMem = 256, lbBw = 50;
    const double fwCpu = 700, fwMem = 256, fwBw = 70;

    NfviAvailableResources total;

    // For each service chain, add one firewall, one load balancer, one server
    total.cpu = numServers * ( serverCpu)+fwCpu+lbCpu;
    total.memory = numServers * (serverMem)+fwMem+lbMem;
    total.bandwidth = numServers * ( serverBw)+fwBw+lbBw;

    return total;
}

void Nfvo::sendServiceChainAck(ServiceChainAck *ack) {
    nfviNodeResources[ack->getNfviNodeId()] = {ack->getAvailableCPU(), ack->getAvailableMemory(), ack->getAvailableBandwidth()};
    send(ack, "tenantSwitchOut");
}
