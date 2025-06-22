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
#include <vector>
#include <algorithm> // For std::min_element if you choose to use it
#include "loadbalancer.h"

#include "packet_m.h" // <--- ADD THIS LINE
using namespace omnetpp;
Define_Module(Loadbalancer);

void Loadbalancer::initialize() {
    serverLoads = std::vector<int>(2, 0); // Assuming 2 servers
}

void Loadbalancer::handleMessage(cMessage *msg) {
    int gateId = msg->getArrivalGate()->getIndex();
    const char *gateName = msg->getArrivalGate()->getBaseName();

    if (strcmp(gateName, "clientIn") == 0) {
        EV << "LoadBalancer: Received request from client (gate " << gateId << ")\n";

        Packet *pkt = dynamic_cast<Packet*>(msg);
        if (!pkt) {
            EV << "LoadBalancer: Received non-Packet message. Dropping.\n";
            delete msg;
            return;
        }

        pkt->setClientGateId(gateId);

        // Find least loaded server
        int assignedServer = -1;
        int minLoad = serverCapacity + 1;
        for (int i = 0; i < serverLoads.size(); ++i) {
            if (serverLoads[i] < minLoad) {
                minLoad = serverLoads[i];
                assignedServer = i;
            }
        }

        if (assignedServer == -1 || serverLoads[assignedServer] >= serverCapacity) {
            EV << "All servers busy. Dropping packet.\n";
            delete pkt;
            return;
        }

        serverLoads[assignedServer]++;
        EV << "Forwarding to server[" << assignedServer << "], current load: " << serverLoads[assignedServer] << "\n";
        send(pkt, "serverOut", assignedServer);
    }
    else if (strcmp(gateName, "serverIn") == 0) {
        EV << "LoadBalancer: Received reply from server (gate " << gateId << ")\n";

        Packet *pkt = dynamic_cast<Packet*>(msg);
        if (!pkt) {
            EV << "Received non-Packet reply. Dropping.\n";
            delete msg;
            return;
        }

        int clientGate = pkt->getClientGateId();

        if (gateId >= 0 && gateId < serverLoads.size()) {
            serverLoads[gateId]--;
            EV << "Server[" << gateId << "] load decremented to " << serverLoads[gateId] << "\n";
        }

        if (clientGate >= 0 && clientGate < gateSize("clientOut")) {
            send(pkt, "clientOut", clientGate);
        } else {
            EV << "Invalid clientGateId. Dropping packet.\n";
            delete pkt;
        }
    }
    else {
        EV << "Unexpected gate: " << gateName << ", dropping message.\n";
        delete msg;
    }
}
