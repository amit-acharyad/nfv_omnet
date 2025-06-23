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
#include "packet_m.h" // <--- ADD THIS LINE

using namespace omnetpp;

class Server : public cSimpleModule
{
  protected:
    virtual void handleMessage(cMessage *msg) override {
        // Cast the received message to your custom Packet type
        Packet *requestPkt = dynamic_cast<Packet*>(msg);
        if (!requestPkt) {
            EV << "Server: Received a non-Packet message. Dropping.\n";
            delete msg;
            return;
        }

        int arrivalGateIndex = msg->getArrivalGate()->getIndex();
        EV << "Server[" << getIndex() << "]: Received request from NFvi node (gate "
           << arrivalGateIndex << "). NFVINOde: " << requestPkt->getClientGateId() << "\n";

        // Simulate some processing time if needed
        simtime_t processingTime = 0.01; // Example processing time
        scheduleAt(simTime() + processingTime, requestPkt); // If you want to delay and then send

        // For now, immediately create a response
        // Use the same packet for response if you only modify its content, or create a new one.
        // It's generally safer to create a new one for clarity in request/response.

        Packet *responsePkt = new Packet("Response");
        // **Crucial:** Copy the clientGateId from the request to the response
        responsePkt->setClientGateId(requestPkt->getClientGateId());

        // Delete the original request packet
        delete requestPkt;

        // Send the response back through the same gate it arrived on
        // You have two gates in server[j].in[0] and server[j].out[0]
        // In NfvServiceChain.ned, server[j].in[0] is connected to loadBalancer.serverOut[j]
        // So, we send back on server[j].out[0]
        EV << "Server[" << getIndex() << "]: Sending response back through gate "
           << arrivalGateIndex << " for nfvinode: " << responsePkt->getClientGateId() << "\n";
        send(responsePkt, "out", arrivalGateIndex); // Using arrivalGateIndex (0) for output gate 0
    }
};

Define_Module(Server);
