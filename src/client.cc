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

#include "client.h"
#include "packet_m.h"
Define_Module(Client);

void Client::initialize() {
    sendInterval = par("sendInterval");
    packetSize = par("packetSize");
    sendEvent = new cMessage("sendEvent");
    scheduleAt(simTime() + sendInterval, sendEvent);
}
void Client::handleMessage(cMessage *msg)  {
    if (msg->isSelfMessage()) {
        Packet *req = new Packet("ClientRequest");

        // Specify gate index 0 explicitly
        req->setClientGateId(gate("eth$o", 0)->getIndex());

        EV << "Client sending Request with clientGateId=" << req->getClientGateId() << endl;

        send(req, "eth$o", 0);
        delete msg;
    }
    else if (auto req = dynamic_cast<Packet *>(msg)) {
        EV << "Client received Request with clientGateId=" << req->getClientGateId() << endl;
        delete req;
    }
    else {
        EV << "Unknown message received. Discarding." << endl;
        delete msg;
    }
}


void Client::finish() {
    cancelAndDelete(sendEvent);
}

