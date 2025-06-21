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
#include "messages/packet_m.h"

using namespace omnetpp;

class Client : public cSimpleModule
{
    cMessage *sendEvent;
    simtime_t sendInterval;
    int packetSize;

  protected:
    virtual void initialize() override {
        sendInterval = par("sendInterval");
        packetSize = par("packetSize");
        sendEvent = new cMessage("sendEvent");
        scheduleAt(simTime() + sendInterval, sendEvent);
    }

    virtual void handleMessage(cMessage *msg) override {
        if (msg == sendEvent) {
            // Create your custom Packet here
            Packet *pkt = new Packet("Request"); // <--- CHANGED HERE
            // You can optionally set clientGateId here, but the LoadBalancer will do it.
            // pkt->setClientGateId(getParentModule()->getIndex()); // Example if you want to set it here
            EV << "Client sending packet\n";
            send(pkt, "out");
            scheduleAt(simTime() + sendInterval, sendEvent);
        } else {
            // It's good practice to dynamic_cast to Packet if you expect Packet types
            Packet *responsePkt = dynamic_cast<Packet*>(msg);
            if (responsePkt) {
                EV << "Client received response from gate ID: " << responsePkt->getClientGateId() << "\n";
            } else {
                EV << "Client received non-Packet response: " << msg->getName() << "\n";
            }
            delete msg;
        }
    }

    virtual void finish() override {
        cancelAndDelete(sendEvent);
    }
};

Define_Module(Client);
