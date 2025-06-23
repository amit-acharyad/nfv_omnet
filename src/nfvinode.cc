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

Define_Module(Nfvinode);

void Nfvinode::initialize()
{
    totalCpuCapacity = par("cpuCapacity");
    totalMemoryCapacity = par("memoryCapacity");
    totalNetworkBandwidth = par("networkBandwidth");

    availableCpu = totalCpuCapacity;
    availableMemory = totalMemoryCapacity;
    availableBandwidth = totalNetworkBandwidth;

    EV << "NFVINODE " << getId() << " Initialized with capacities: CPU=" << totalCpuCapacity
       << " MEM=" << totalMemoryCapacity << " BW=" << totalNetworkBandwidth << endl;
}

void Nfvinode::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        delete msg;
        return;
    }
    //Handle VNFDeployment requests
    if (auto req = dynamic_cast<VnfDeploymentRequest *>(msg)) {
        EV << "NFVINODE " << getId() << ": Received VNF Deployment Request for " << req->getVnfType()
           << " (ReqId: " << req->getRequestId() << ")" << endl;

        auto resp = new VnfDeploymentResponse("VnfDeploymentResponse");
        resp->setRequestId(req->getRequestId());
        resp->setNfviNodeId(getId());

        if (availableCpu >= req->getRequiredCpu() &&
            availableMemory >= req->getRequiredMemory() &&
            availableBandwidth >= req->getRequiredBandwidth()) {

            cModuleType *vnfType = nullptr;

            if (strcmp(req->getVnfType(), "Firewall") == 0) {
                EV<<"Firewall Comp resulted TRUE"<<endl;
                vnfType = cModuleType::find("omnet_nfv.Firewall");
            } else if (strcmp(req->getVnfType(), "Loadbalancer") == 0) {
                EV<<"Loadbalcner Comp resulted TRUE"<<endl;

                vnfType = cModuleType::find("omnet_nfv.Loadbalancer");
            } else if (strcmp(req->getVnfType(), "Server") == 0) {
                vnfType = cModuleType::find("omnet_nfv.Server");
            }
            EV<<"The VNF type is"<<vnfType<<endl;

            if (vnfType) {
                static int vnfIndex = 0;
                std::string vnfName = std::string("vnf_") + req->getVnfType() + "_" + std::to_string(vnfIndex++);
                cModule *vnf = vnfType->create(vnfName.c_str(), this);
                vnf->buildInside();
                vnf->callInitialize();

                availableCpu -= req->getRequiredCpu();
                availableMemory -= req->getRequiredMemory();
                availableBandwidth -= req->getRequiredBandwidth();

                resp->setSuccess(true);
                resp->setDeploymentId(vnf->getFullName());

                EV << "NFVINode " << getId() << ": Successfully deployed " << req->getVnfType()
                   << ". Remaining Resources: CPU=" << availableCpu
                   << " MEM=" << availableMemory << " BW=" << availableBandwidth << endl;
            } else {
                resp->setSuccess(false);
                resp->setErrorMessage("Unknown VNF type requested");
                EV << "NFVINode " << getId() << ": Failed to deploy VNF. Unknown type: "
                   << req->getVnfType() << endl;
            }
        } else {
            resp->setSuccess(false);
            resp->setErrorMessage("Insufficient resources on the NFVI node");
            EV << "NFVINode " << getId() << ": Failed to deploy " << req->getVnfType()
               << " due to insufficient resources." << endl;
        }


        send(resp, "managementGate$o");
        delete msg;
        return;
    }
    //Handle Data Plane Packets
    Packet* packet=dynamic_cast<Packet*>(msg);
    if(packet){
        cGate *arrivalGate=msg->getArrivalGate();
        EV<<"Arrival Gate for the pkt is "<<arrivalGate->getName()<<endl;
        if(arrivalGate->isName("eth$i"))

        {
            EV<<"NFVINODE"<<getId()<<":Received data packet from external network."<<endl;
                    cModule* targetVnf=nullptr;
                    for (auto const& [name,module]:deployedVnfs){
                        if(strcmp(module->getNedTypeName(),"Firewall")==0){
                            targetVnf=module;
                            break;
                        }
                    }
                    if(targetVnf){
                        send(packet,targetVnf->gate(0));
                        EV<<"NFVINode"<<getId()<<":Forwarded to"<<targetVnf->getFullName()
            <<endl;
                    }else{
                        EV<<"NFVI Node"<<getId()<<": No Suitable VNF founf to forward to dropping packet."<<endl;
                        delete packet;
                    }
        }



    else if(arrivalGate->getOwnerModule()!=this){
        cModule *senderVnf =arrivalGate->getOwnerModule();
        EV<<"NFVINODE"<<getId()<<": Received data packet from internal VNF: "<<senderVnf->getFullName()
<<endl;
        send (packet,"eth$o",0);
        EV<<"NFVINODE "<<getId()<<": Forwarded packet from VNF to external network"<<endl;

    }
    else{
        EV<<"NFVINOde "<<getId()<<": Received unhandled message type."<<endl;
        delete msg;
    }

    }

}


void Nfvinode::finish()
{
    EV << "NFVINode " << getId()
       << ": Simulation Finished. Final Available resources CPU=" << availableCpu
       << " MEM=" << availableMemory << " BW=" << availableBandwidth << endl;
}


