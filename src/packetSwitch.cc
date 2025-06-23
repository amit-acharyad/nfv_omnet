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

#include "packetSwitch.h"
#include <omnetpp.h>
#include "packet_m.h"  // Include your generated message header
Define_Module(PacketSwitch);

using namespace omnetpp;
void PacketSwitch::initialize() {
    EV<<"PacketSwitch:Initialized with "<<gateSize("port")<<"ports."<<endl;
    numPorts = par("numPorts");
    if(numPorts!=gateSize("port")){
        EV_WARN<<"PacketSwitch :numPports parameter("<<numPorts<<") does notmatch actual gateSize"<<gateSize("port")<<endl;

    }
}

void PacketSwitch::handleMessage(cMessage *msg) {
    Packet* packet=dynamic_cast<Packet*>(msg);
    if(!packet){
        EV<<"PacketSwitch: received non packetmessage deleting"<<endl;
        delete msg;
        return;
    }
    cGate *arrivalGate=msg->getArrivalGate();
    EV<<"PacketSwitch: Received packet"<<packet->getName()<<"on gate"<<arrivalGate->getFullName()<<endl;
    int arrivalGateIndex=arrivalGate->getIndex();
    int numTotalPorts=gateSize("port");

    int outputGatesIndex=-1;
    if(arrivalGateIndex>=0 && arrivalGateIndex<=3){
        outputGatesIndex=4;
        EV<<"PacketSwitch :Packet from client gate"<<arrivalGateIndex<<",sending towards NFVI node 0 data plane."<<endl;



    }
    else if(arrivalGateIndex>=4 && arrivalGateIndex<=5){
        if (arrivalGateIndex == 4) { // From NFVINode 0
                    outputGatesIndex = 0; // Send to Client 0
                } else if (arrivalGateIndex == 5) { // From NFVINode 1
                    outputGatesIndex = 1; // Send to Client 1
                }
                EV << "PacketSwitch: Packet from NFVINode gate " << arrivalGateIndex << ", sending back towards clients." << endl;
    }
    else {
        EV << "PacketSwitch: Unrecognized arrival gate index " << arrivalGateIndex << ". Dropping packet." << endl;
               delete packet;
               return;
    }

    if (outputGatesIndex != -1 && outputGatesIndex < numTotalPorts && outputGatesIndex != arrivalGateIndex) {
            send(packet, "port$o", outputGatesIndex); // Send packet out through the chosen gate
            EV << "PacketSwitch: Forwarded packet " << packet->getName() << " out gate port[" << outputGatesIndex << "]" << endl;
        } else {
            EV << "PacketSwitch: Could not determine valid output gate or circular path. Dropping packet " << packet->getName() << endl;
            delete packet; // Drop packet if no valid output gate found
        }

}

