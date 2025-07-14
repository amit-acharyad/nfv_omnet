
#include "tenantSwitch.h"
#include "servicemsg_m.h"
Define_Module(TenantSwitch);

void TenantSwitch::initialize()
{
    EV<<"Initializing tenant Switch"<<endl;
}

void TenantSwitch::handleMessage(cMessage *msg)
{
    int arrivalGateId = msg->getArrivalGateId();

    if (arrivalGateId == gate("fromNfvo")->getId()) {
        forwardToEnterprise(msg);
    } else {
        // Assume it's from some tenant (enterprise client)
        forwardToNfvo(msg);
    }
}

void TenantSwitch::forwardToNfvo(cMessage *msg)
{
    // Optional: extract enterprise ID and store gate index
    if (auto *req = dynamic_cast<ServiceChainRequest *>(msg)) {
        int enterpriseId = req->getEnterpriseId();
        int gateIndex = msg->getArrivalGate()->getIndex();

        // Store if not already mapped
        if (enterpriseIdToGateIndex.find(enterpriseId) == enterpriseIdToGateIndex.end()) {
            enterpriseIdToGateIndex[enterpriseId] = gateIndex;
        }
    }

    send(msg, "toNfvo");
}

void TenantSwitch::forwardToEnterprise(cMessage *msg)
{
    if (auto *ack = dynamic_cast<ServiceChainAck *>(msg)) {
        int enterpriseId = ack->getEnterpriseId();
        if (enterpriseIdToGateIndex.find(enterpriseId) != enterpriseIdToGateIndex.end()) {
            int gateIndex = enterpriseIdToGateIndex[enterpriseId];
            send(msg, "toTenants", gateIndex);
        } else {
            EV << "Unknown enterpriseId " << enterpriseId << " — dropping message\n";
            delete msg;
        }
    } else {
        EV << "Unknown message type from NFVO — dropping\n";
        delete msg;
    }
}
