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

#ifndef __OMNET_NFV_VNFMANAGER_H_
#define __OMNET_NFV_VNFMANAGER_H_

#include <omnetpp.h>
#include "nfvMessages_m.h"
#include <map>
#include <vector>
using namespace omnetpp;

struct DeployedVnfInfo{
    std::string name;
    VnfType type;
    int ipAddress;
    int nfviNodeId;
};
class Vnfmanager : public cSimpleModule
{
  protected:
    int numNfviNodes;
    int nextVnfIp;
    // Data structures for managing deployments
       std::vector<int> nfviNodeIds; // To store IDs of connected NFVINodes
       std::map<std::string, DeployedVnfInfo> deployedVnfs; // Map VNF name to its info
       struct VnfDeploymentConfig {
               VnfType type;
               std::string name;
               double cpu;
               double mem;
               double bw;
               // Add other config needed specific to this type for deployment
           };
           std::vector<VnfDeploymentConfig> serviceChainBlueprint;
           std::vector<int>serverVnfIPs;
           int receivedDeployments = 0;


           virtual void initialize() override;
               virtual void handleMessage(cMessage *msg) override;
               virtual void handleSelfMessage(cMessage *msg); // New method for self-messages
               virtual void deployServiceChain(); // New method to encapsulate deployment logic
               virtual void finish() override;
               virtual void handleVnfDeploymentResponse(VnfDeploymentResponse *resp);
  public:
               cGate *nfvoGate;
               cGate *nfviNodeGate;
};

#endif
