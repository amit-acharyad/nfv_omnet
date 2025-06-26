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
    EV<<"PacketSwitch:Initialized with "<<gateSize("portIn")<<"ports."<<endl;
    numPorts = par("numPorts");
    if(numPorts!=gateSize("portIn")){
        EV_WARN<<"PacketSwitch :numPports parameter("<<numPorts<<") does notmatch actual gateSize"<<gateSize("portIn")<<endl;

    }
}

void PacketSwitch::handleMessage(cMessage *msg) {
    Packet *pkt = check_and_cast<Packet *>(msg);
    int arrivalGateIndex = msg->getArrivalGate()->getIndex();


    if (pkt->isRegistration()) {
        int senderIp = pkt->getSourceAddress();
        ipToPort[senderIp] = arrivalGateIndex;
        EV << "Registered IP " << senderIp << " on portIn[" << arrivalGateIndex << "]\n";
        delete pkt;
        return;
    }


    int destIp = pkt->getDestinationAddress();
    auto it = ipToPort.find(destIp);
    if (it != ipToPort.end()) {
        int outPort = it->second;
        send(pkt, "portOut", outPort);
        EV << "Forwarded packet to IP " << destIp << " via portOut[" << outPort << "]\n";
    } else {
        EV_WARN << "Destination IP " << destIp << " unknown. Dropping.\n";
        delete pkt;
    }
}


