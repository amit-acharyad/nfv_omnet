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

    int sourceAddress=par("sourceAddress");
    Packet *reg = new Packet("Register");

        reg->setSourceAddress(sourceAddress);  // assuming you have this param
        reg->setIsRegistration(true);
        send(reg, "ethOut");
        sendEvent = new cMessage("sendEvent");
        sendInterval=par("sendInterval");
         scheduleAt(simTime() + sendInterval, sendEvent);  // send after 1s
}
void Client::handleMessage(cMessage *msg)  {
    if(msg->isSelfMessage()){
        EV<<"Clinet sending request"<<endl;
        Packet *req=new Packet("Client Request");
        int sourceIp=par("sourceAddress");
           int destinationIp=par("destinationAddress");
           req->setSourceAddress(sourceIp);  // assuming you have this param
               req->setDestinationAddress(destinationIp);
               req->setIsRegistration(false);
               send(req, "ethOut");

    }
    else if (auto pkt = dynamic_cast<Packet *>(msg)) {
           // Received a packet from the network
           EV << "Client received response: " << pkt->getName() <<"from"<< pkt->getSourceAddress()<< "\n";
           delete pkt;
       }
       else {
           EV_WARN << "Unknown message received, discarding.\n";
           delete msg;
       }





}


void Client::finish() {
    cancelAndDelete(sendEvent);
}

