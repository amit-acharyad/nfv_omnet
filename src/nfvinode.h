#ifndef __OMNET_NFV_NFVINODE_H_
#define __OMNET_NFV_NFVINODE_H_

#include <omnetpp.h>
#include "../messages/nfvMessages_m.h"
#include "../messages/packet_m.h"
#include "firewall.h"
#include "loadbalancer.h"
#include "server.h"
#include <map>
#include <string>
#include <vector>
#include <queue>
#include "../messages/vnfRegistration_m.h"


using namespace omnetpp;

// Structure to track deployed VNFs internally for routing and management
// Structure to track deployed VNFs internally for routing and management
struct DeployedVnfModule {
    std::string name;       // Name of the VNF instance
    VnfType type;           // Type of the VNF (e.g., VNF_TYPE_FIREWALL)
    int ipAddress;          // The IP address assigned to this VNF
    cModule* moduleRef;     // Pointer to the actual VNF module instance
};
struct ServiceChainInfo {
    int enterpriseId;
    std::vector<DeployedVnfModule> vnfsOrdered;  // Full info: name, type, ip, module
    bool wiringDone = false;
};




class Nfvinode : public cSimpleModule
{
  protected:
    //Current available resources
    int id;
    double availableCpu;
    double availableMemory;
    double availableBandwidth;
    //Total capacity
    double totalCpuCapacity;
    double totalMemoryCapacity;
    double totalNetworkBandwidth;
    int vnfIdCounter;
    std::map<int, std::queue<Packet*>> bufferedPacketsPerEnterprise;
    std::map<int, ServiceChainInfo> serviceChains;  // enterpriseId → ServiceChainInfo
    std::map<int, DeployedVnfModule> deployedVnfsByIp;
    std::map<int, int> vnfIpToEnterpriseId;
    std::map<int, int> vnfIpToInternalGateIndex;
    int nextAvailableGateIndex = 0;
  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void handleVnfDeploymentRequest(VnfDeploymentRequest *req); // New handler
    virtual void handleDataPacket(Packet *packet,cGate *arrivalGate); // New handler for clarity
    virtual void wireInternalServiceChain(int enterpriseId);
    virtual int getEnterpriseIdForVnfIp(int ip);
};

#endif
