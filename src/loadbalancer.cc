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
    EV<<"LoadBalancer: Initialized."<<endl;
    currentServerIndex=0;
    int serverCount=serverIPs.size();

    if (serverIPs.empty()) {
            EV_ERROR << "LoadBalancer: No backend server IPs configured! LoadBalancer will drop packets." << endl;
        } else {
            EV << "LoadBalancer: Configured with " << serverCount << " backend servers." <<serverIPs.size()<< endl;
        }

}

void Loadbalancer::handleMessage(cMessage *msg) {
    Packet *pkt = dynamic_cast<Packet*>(msg);
    if (!pkt) {
        EV << "Loadbalancer received a non-Packet message, deleting.\n";
        delete msg;
        return;
    }

    EV << "LoadBalancer: Received packet "
       << pkt->getName()
       << " (Src: " << pkt->getSourceAddress()
       << ", Dst: " << pkt->getDestinationAddress() << ")" << endl;

    if (serverIPs.empty()) {
        EV_ERROR << "LoadBalancer: No backend servers to forward to. Dropping packet." << endl;
        delete pkt;
        return;
    }
    cGate* arrivalGate = msg->getArrivalGate();

    if (arrivalGate->isName("inServer")) {
        // handle response from server — maybe forward to firewall or client
        send(pkt, "out");  // send to firewall
        return;
    }


    int chosenServerIp = serverIPs[currentServerIndex];
    int chosenGateIndex = currentServerIndex;  // same index assumed for outServer[]
    currentServerIndex = (currentServerIndex + 1) % serverIPs.size();

    pkt->setDestinationAddress(chosenServerIp);
    EV << "LoadBalancer: Redirected packet to server IP: " << chosenServerIp
       << ", sending via outServer[" << chosenGateIndex << "]\n";

    send(pkt, "outServer", chosenGateIndex);
}

void Loadbalancer::finish()
{
}
