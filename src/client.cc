#include "client.h"
#include "../messages/packet_m.h"
Define_Module(Client);
void Client::initialize() {
    int sourceAddress = par("sourceAddress");
    int index = getIndex();
    int destAddr;
    switch (index % 4) {
        case 0: destAddr = 102; break;
        case 1: destAddr = 106; break;
        case 2: destAddr = 109; break;
        case 3: destAddr = 113; break;
    }
    destinationIp = destAddr;
    Packet *reg = new Packet("Register");
    reg->setSourceAddress(sourceAddress);
    reg->setIsRegistration(true);
    send(reg, "ethOut");
    sendEvent = new cMessage("sendEvent");
    sendInterval = par("sendInterval");

    // Try first request after initial delay
    scheduleAt(simTime() + sendInterval, sendEvent);
}

void Client::handleMessage(cMessage *msg) {
    if (msg->isSelfMessage()) {
        if (!awaitingAck && retryCount >= maxRetries) {
            EV << "Client gave up after " << retryCount << " retries.\n";
            delete msg;
            return;
        }

        EV << "Client retrying request to " << destinationIp << " (attempt " << retryCount + 1 << ")\n";

        Packet *req = new Packet("ClientRequest");
        req->setSourceAddress(par("sourceAddress"));
        req->setDestinationAddress(destinationIp);
        req->setIsRegistration(false);
        req->setIsProbe(true);  // Optional: distinguish probe packets
        send(req, "ethOut");

        retryCount++;

        // Reschedule if still waiting
        if (awaitingAck && retryCount < maxRetries) {
            scheduleAt(simTime() + sendInterval, sendEvent);
        }
    }
    else if (auto *pkt = dynamic_cast<Packet *>(msg)) {
        if (pkt->getName() == std::string("PacketForwardedAck")) {
            if (pkt->getDestinationAddress() == destinationIp) {
                EV << "Client received forward confirmation from PacketSwitch. Stopping retries.\n";
                awaitingAck = false;
            }
        } else {
            EV << "Client received response: " << pkt->getName() << " from " << pkt->getSourceAddress() << "\n";
        }
        delete pkt;
    }
    else {
        EV_WARN << "Unknown message received, discarding.\n";
        delete msg;
    }
}

void Client::finish() {
    cancelAndDelete(sendEvent);
}

