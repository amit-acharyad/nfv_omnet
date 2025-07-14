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
#include "server.h"
using namespace omnetpp;

Define_Module(Server);

void Server::initialize()
{
    EV << "WebServerVNF: Initialized." << endl;
    // Get its own IP address from parameters (set by VnfManager/NFVINode)
    myIpAddress = par("myIpAddress").intValue();
    EV << "WebServerVNF: My IP is: " << myIpAddress << endl;

}

void Server::handleMessage(cMessage *msg)
{
    Packet* requestPacket = dynamic_cast<Packet*>(msg);
    if (!requestPacket) {
        EV << "WebServerVNF: Received non-packet message. Deleting." << endl;
        delete msg;
        return;
    }

    EV << "WebServerVNF: Received request " << requestPacket->getName()
       << " (Src: " << requestPacket->getSourceAddress()
       << ", Dst: " << requestPacket->getDestinationAddress()
       << ") on gate " << msg->getArrivalGate()->getFullName() << endl; // Use getFullName for gate info

    // --- Simulate Processing (optional) ---
    // If you want to simulate delay, schedule a self-message or the response packet
    // For now, let's create and send response immediately as before.
    // simtime_t processingTime = 0.01;
    // scheduleAt(simTime() + processingTime, requestPacket->dup()); // Duplicate if processing, then send original to a timer
    // delete requestPacket; // Delete original if duplicating

    // --- Create Response Packet ---
    Packet* responsePacket = new Packet("Response");

    // **CRUCIAL CHANGE:** Set Source and Destination addresses for the response
    responsePacket->setSourceAddress(myIpAddress); // Response comes from this server's IP
    responsePacket->setDestinationAddress(requestPacket->getSourceAddress()); // Goes back to the original client's IP

    // Log the response details before sending
    EV << "WebServerVNF: Sending response (Src: " << responsePacket->getSourceAddress()
       << ", Dst: " << responsePacket->getDestinationAddress() << ")" << endl;

    // Delete the incoming request packet, as it's been processed
    delete requestPacket;

    // Send the response packet back through the *same gate* it arrived on.
    // Assuming your WebServerVNF has an 'out' gate for replies.
    // If you have 'in in;' and 'out out;' in WebServerVNF.ned, then just 'send(responsePacket, "out");' is usually sufficient.
    // If 'in' and 'out' are vectors, you might need to use getArrivalGate()->getIndex() if the index is relevant for the output gate.
    // Based on typical VNF setup, a single 'out' gate is common.
    send(responsePacket, "out"); // Send out the single 'out' gate
}

void Server::finish()
{
}

