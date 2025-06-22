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

void Vnfmanager::initialize()
{
    nextRequestedId=0;//Initialize requestId counter to 0
    VnfDeploymentRequest *req1=new VnfDeploymentRequest("Deploy Firewall");
    req1->setVnfType("Firewall");
    req1->setRequiredCpu(500);
    req1->setRequiredMemory(256);
    req1->setRequiredBandwidth(100);
    req1->setRequestId(++nextRequestedId);
    send(req1,"nfviNodeGate$o",0);
    EV<<"VNF Manager: Sent request (ID "<<req1->getRequestId()<<") to deploy Firewall on NFVInode 0."<<endl;

    VnfDeploymentRequest *req2=new VnfDeploymentRequest("Deploy Server");
    req2->setVnfType("Server");
    req2->setRequiredCpu(1500);
    req2->setRequiredMemory(512);
    req2->setRequestId(++nextRequestedId);
    req2->setRequiredBandwidth(200);
    send(req2,"nfviNodeGate$o",1);
    EV<<"VNFManager:sent request(ID "<<req2->getRequestId()<<") to deploy Server on NFviNode1."<<endl;


    VnfDeploymentRequest *req3=new VnfDeploymentRequest ("Deploy Loadbalancer");
    req3->setVnfType("Loadbalancer");
    req3->setRequestId(++nextRequestedId);
    req3->setRequiredCpu(300);
    req3->setRequiredMemory(128);
    req3->setRequiredBandwidth(50);
    send(req3,"nfviNodeGate$o",0);
    EV<<"VNFManager:sent request(ID "<<req3->getRequestId()<<") to deploy Server on NFviNode."<<endl;




}

void Vnfmanager::handleMessage(cMessage *msg)
{

    if(dynamic_cast<VnfDeploymentResponse*> (msg)){
        VnfDeploymentResponse *resp= dynamic_cast<VnfDeploymentResponse*>(msg);
        EV<<"VNF manager :received deployment response for requeest Id"<<resp->getRequestId()<<"from NFVINode "<<resp->getNfviNodeId()
<<".Success: "<<(resp->getSuccess()?"YES":"NO")    <<endl;
        if(resp->getSuccess()){
            EV<<"Deployed VNF ID:"<<resp->getDeploymentId()<<endl;

        }else{
            EV<<"ERROR: "<<resp->getErrorMessage()<<endl;
        }
    }
    delete msg;
}
void Vnfmanager::finish(){

}
