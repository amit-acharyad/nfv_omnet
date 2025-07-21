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

#include "enterpriseClient.h"
#include "../messages/servicemsg_m.h"

Define_Module(EnterpriseClient);


EnterpriseClient::EnterpriseClient() : sendRequestEvent(nullptr) {}

EnterpriseClient::~EnterpriseClient() {
    cancelAndDelete(sendRequestEvent);
}

void EnterpriseClient::initialize() {
    enterpriseId = par("enterpriseId");
    serviceChainType = par("serviceChainType").stringValue();
    desiredServerCount = par("desiredServerCount");
    requestTime = par("requestTime");

    sendRequestEvent = new cMessage("sendRequestEvent");
    scheduleAt(requestTime, sendRequestEvent);
}

void EnterpriseClient::handleMessage(cMessage* msg) {
    if (msg == sendRequestEvent) {
        sendServiceChainRequest();
    } else if (auto* ack = dynamic_cast<ServiceChainAck*>(msg)) {
        handleServiceChainAck(ack);
    } else {
        EV << "Received unknown message type\n";
        delete msg;
    }
}

void EnterpriseClient::sendServiceChainRequest() {
    ServiceChainRequest* req = new ServiceChainRequest("serviceChainRequest");
    req->setEnterpriseId(enterpriseId);
    req->setChainType(serviceChainType.c_str());
    req->setDesiredServerCount(desiredServerCount);

    EV << "EnterpriseClient[" << enterpriseId << "] sending ServiceChainRequest\n";
    send(req, "out");
}

void EnterpriseClient::handleServiceChainAck(ServiceChainAck* ack) {
    if (ack->getSuccess()) {
        EV << "EnterpriseClient[" << enterpriseId << "] received ACK: Deployment successful on NFVI Node " << ack->getNfviNodeId() << "\n";
    } else {
        EV << "EnterpriseClient[" << enterpriseId << "] received ACK: Deployment failed - " << ack->getMessageinfo() << "\n";
    }
    delete ack;
}
