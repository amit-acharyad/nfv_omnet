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
    EV<<"Client sending message ";
    int sourceIp=par("sourceAddress");
    int destinationIp=par("destinationAddress");
        Packet *pkt = new Packet("Register");
            pkt->setSourceAddress(sourceIp);  // assuming you have this param
            pkt->setDestinationAddress(destinationIp);
            pkt->setIsRegistration(false);
            send(pkt, "ethOut");

}


void Client::finish() {
    cancelAndDelete(sendEvent);
}

