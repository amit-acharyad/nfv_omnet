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



#include <omnetpp.h>
#include "packet_m.h"
#include "firewall.h"
using namespace omnetpp;
Define_Module(Firewall);

void Firewall::handleMessage(cMessage *msg)  {
        // Cast to Packet (optional, but good for type awareness)
        Packet *pkt = dynamic_cast<Packet*>(msg);
        if (!pkt) {
            EV << "Firewall received a non-Packet message, forwarding anyway: " << msg->getName() << "\n";
        }

        int gateIndex = msg->getArrivalGate()->getIndex();
        const char* gateName = msg->getArrivalGate()->getName();
        EV<<"Firewall"<<getFullPath()<<":Received Paccket"<<endl;
        //Simulate some delay
        scheduleAt(simTime()+0.001,msg);
        //real firewall will have filtering logic here
        if (strcmp(gateName, "in") == 0) {
            // From client side -> forward to LoadBalancer
            EV << "Firewall Vnf  " << gateIndex << "forwarding  to NFVINODE.\n";
            send(msg, "out", gateIndex);
        }  else {
            EV << "Firewall: Unexpected gate: " << gateName << ", dropping message.\n";
            delete msg;
        }
    }


void Firewall::initialize(){

}


