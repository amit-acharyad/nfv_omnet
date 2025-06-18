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
#include "packet_m.h" // <--- ADD THIS LINE

using namespace omnetpp;
class Loadbalancer : public cSimpleModule
{
  private:
    int serverCapacity = 2; // Maximum concurrent requests per server
    std::vector<int> serverLoads;  // Stores current load (number of active requests) for each server

  protected:
    virtual void initialize() override {
            serverLoads = std::vector<int>(2, 0);
        }



    virtual void handleMessage(cMessage *msg) override {
        int gateId = msg->getArrivalGate()->getIndex();
        const char *gateName = msg->getArrivalGate()->getBaseName();

        if (strcmp(gateName, "clientIn") == 0) {
            EV << "LoadBalancer: Received request from client (gate " << gateId << ")\n";

            // **Crucial:** Cast the cMessage to your custom Packet type
            Packet *pkt = dynamic_cast<Packet*>(msg);
            if (!pkt) {
                EV << "LoadBalancer: Received non-Packet message from client. Dropping.\n";
                delete msg; // Delete the generic cMessage
                return;
            }

            // **Store the original client's gate index in the packet**
            pkt->setClientGateId(gateId);

            // --- Load Balancing Logic (Least Loaded) ---
            int assignedServer = -1;
            int minLoad = serverCapacity + 1; // Initialize with a value higher than any possible load

            // Iterate through available servers to find the least loaded one
            for (int i = 0; i < serverLoads.size(); ++i) {
                if (serverLoads[i] < minLoad) {
                    minLoad = serverLoads[i];
                    assignedServer = i;
                }
            }

            if (assignedServer == -1 || serverLoads[assignedServer] >= serverCapacity) {
                EV << "LoadBalancer: All servers busy or no server found. Dropping packet from client[" << gateId << "].\n";
                delete pkt; // Delete the custom Packet
                return;
            }

            // Increment the load for the chosen server
            serverLoads[assignedServer]++;
            EV << "LoadBalancer: Forwarding packet from client[" << gateId << "] to server[" << assignedServer
               << "]. Server[" << assignedServer << "] current load: " << serverLoads[assignedServer] << "\n";

            // Send the packet to the selected server's input gate
            send(pkt, "serverOut", assignedServer);
        }
        else if (strcmp(gateName, "serverIn") == 0) {
            EV << "LoadBalancer: Received reply from server (gate " << gateId << ")\n";

            // **Crucial:** Cast the cMessage to your custom Packet type
            Packet *pkt = dynamic_cast<Packet*>(msg);
            if (!pkt) {
                EV << "LoadBalancer: Received non-Packet message from server. Dropping.\n";
                delete msg; // Delete the generic cMessage
                return;
            }

            // **Retrieve the original client's gate index from the packet**
            int clientGate = pkt->getClientGateId();
            EV<<"Clinet gate is "<<clientGate<<"\n";
            // Decrement the load for the server that sent the response (gateId is the server's index)
            if (gateId >= 0 && gateId < serverLoads.size()) {
                serverLoads[gateId]--;
                EV << "LoadBalancer: Server[" << gateId << "] load decremented to: " << serverLoads[gateId] << "\n";
            } else {
                EV << "LoadBalancer: Error: Received response from invalid server gate " << gateId << ".\n";
                // Even if invalid gate, try to forward if clientGate is valid
            }

            // Send the response back to the original client
            if (clientGate >= 0 && clientGate < gateSize("clientOut")) {
                 EV << "LoadBalancer: Returning response to client (gate " << clientGate << ").\n";
                 send(pkt, "clientOut", clientGate);
            } else {
                EV << "LoadBalancer: Error: Client gate ID " << clientGate << " retrieved from packet is invalid. Dropping response.\n";
                delete pkt; // Drop if cannot route back
            }
        }
        else {
            EV << "LoadBalancer: Unexpected message arrival gate: " << gateName << ", dropping message.\n";
            delete msg;
        }
    }
};
Define_Module(Loadbalancer);
