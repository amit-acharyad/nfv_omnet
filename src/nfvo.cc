#include "nfvo.h"
#include "servicemsg_m.h"
#include "deploymentplan_m.h"
#include "nfvMessages_m.h"
#include <string>

Define_Module(Nfvo);

void Nfvo::initialize() {
    // Nothing special at startup
}

void Nfvo::handleMessage(cMessage *msg) {
    if (auto *req = dynamic_cast<ServiceChainRequest *>(msg)) {
        handleServiceChainRequest(req);
    }else if (auto *res = dynamic_cast<VnfDeploymentResponse *>(msg)) {
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

    // For now, pick NFVINode 0 statically
    int nfviNodeId = 0;

    sendDeploymentPlan(enterpriseId, nfviNodeId, chainType, numServers);


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

void Nfvo::sendServiceChainAck(VnfDeploymentResponse *resp) {

    ServiceChainAck *ack=new ServiceChainAck();
    ack->setEnterpriseId(resp->getRequestId());
    ack->setSuccess(true);
    ack->setMessageinfo("Successfully deployed service chain");
    ack->setNfviNodeId(0);
    send(ack, "tenantSwitchOut");
}
