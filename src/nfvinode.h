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

#ifndef __OMNET_NFV_NFVINODE_H_
#define __OMNET_NFV_NFVINODE_H_

#include <omnetpp.h>
#include "nfvMessages_m.h"
#include "packet_m.h"
#include "firewall.h"
#include "loadbalancer.h"
#include "server.h"
#include <map>
#include <string>
#include <vector>
#include <queue>

using namespace omnetpp;

// Structure to track deployed VNFs internally for routing and management
// Structure to track deployed VNFs internally for routing and management
struct DeployedVnfModule {
    std::string name;       // Name of the VNF instance
    VnfType type;           // Type of the VNF (e.g., VNF_TYPE_FIREWALL)
    int ipAddress;          // The IP address assigned to this VNF
    cModule* moduleRef;     // Pointer to the actual VNF module instance
};


class Nfvinode : public cSimpleModule
{
  protected:
    //Current available resources
    int dataPlaneIp;
    double availableCpu;
    double availableMemory;
    double availableBandwidth;
    //Total capacity
    double totalCpuCapacity;
    double totalMemoryCapacity;
    double totalNetworkBandwidth;

    int vnfIdCounter;

    std::map<int, DeployedVnfModule> deployedVnfsByIp;
    std::map<std::string, DeployedVnfModule> deployedVnfsByName;
    bool internalConnectionsDone;
    std::queue<Packet*> bufferedPackets;

  protected:
        virtual void initialize() override;
            virtual void handleMessage(cMessage *msg) override;
            virtual void handleVnfDeploymentRequest(VnfDeploymentRequest *req); // New handler
            virtual void handleDataPacket(Packet *packet, cGate *arrivalGate); // New handler for clarity
            virtual void wireInternalServiceChain();
};

#endif
