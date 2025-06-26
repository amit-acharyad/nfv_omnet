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

    const char* ipListStr = par("serverIPs").stringValue();
    cStringTokenizer tokenizer(ipListStr);
    while (tokenizer.hasMoreTokens()) {
        const char* token = tokenizer.nextToken();
        serverIPs.push_back(atoi(token));
    }




    if (serverIPs.empty()) {
            EV_ERROR << "LoadBalancer: No backend server IPs configured! LoadBalancer will drop packets." << endl;
        } else {
            EV << "LoadBalancer: Configured with " << serverIPs.size() << " backend servers." << endl;
        }

}

void Loadbalancer::handleMessage(cMessage *msg)  {
        // Cast to Packet (optional, but good for type awareness)
        Packet *pkt = dynamic_cast<Packet*>(msg);
        if (!pkt) {
            EV << "Loadbalancer received a non-Packet message, Deleting " <<"\n";
            delete msg;
            return;
        }
        EV << "LoadBalancer: Received packet " << pkt->getName()
               << " (Src: " << pkt->getSourceAddress()
               << ", Dst: " << pkt->getDestinationAddress() << ")" << endl;

            if (serverIPs.empty()) {
                EV_ERROR << "LoadBalancer: No backend servers to forward to. Dropping packet." << endl;
                delete pkt;
                return;
            }

            // --- Load Balancing Logic (Round Robin) ---
                int chosenServerIp = serverIPs[currentServerIndex];
                currentServerIndex = (currentServerIndex + 1) % serverIPs.size(); // Move to next server

                pkt->setDestinationAddress(chosenServerIp); // Redirect to chosen WebServerVNF
                EV << "LoadBalancer: Redirected packet destination to WebServerVNF IP: " << chosenServerIp << endl;

                // Assuming the LoadBalancer has an 'out' gate defined for chaining
                send(pkt, "out"); // Send out to the next hop in the chain (chosen WebServerVNF)



    }
void Loadbalancer::finish()
{
    // Optional: report statistics
}
