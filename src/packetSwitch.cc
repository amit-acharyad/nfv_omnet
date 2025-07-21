#include "packetSwitch.h"
#include <omnetpp.h>
#include "../messages/packet_m.h"  // Include your generated message header
#include "../messages/vnfRegistration_m.h"

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
    Packet *pkt = dynamic_cast<Packet *>(msg);
    int arrivalGateIndex = msg->getArrivalGate()->getIndex();

    if(pkt)
    {
        if (pkt->isRegistration()) {
               int senderIp = pkt->getSourceAddress();
               ipToPort[senderIp] = arrivalGateIndex;
               EV << "Registered IP " << senderIp << " on portIn[" << arrivalGateIndex << "]\n";
               delete pkt;
               return;
           }
    }

    if (auto* reg = dynamic_cast<VnfRegistrationMessage*>(msg)) {
        EV<<"Packet came for registration vnf"<<endl;
        int vnfIp = reg->getVnfIp();
        int gateIndex = msg->getArrivalGate()->getIndex(); // From which NFVI node this arrived
        EV<<"IPTONODEGATEMAPSETTING"<<endl;
        ipToNfviNodeGate[vnfIp] = gateIndex;

        EV << "Registered VNF IP " << vnfIp << " to gate index " << gateIndex << " (NFVINode)\n";
        delete msg;
        return;
    }
    int destIp = pkt->getDestinationAddress();

    // First check: is destination registered client?
    auto it = ipToPort.find(destIp);
    if (it != ipToPort.end()) {
        int outPort = it->second;
        send(pkt, "portOut", outPort);
        EV << "Forwarded packet to IP " << destIp << " via portOut[" << outPort << "]\n";
        // Send ACK back to sender
        if(pkt){
            if(pkt->isProbe()){

                    Packet *ack = new Packet("PacketForwardedAck");
                    ack->setSourceAddress(destIp);         // The destination we forwarded to
                    ack->setDestinationAddress(pkt->getSourceAddress()); // Client that sent it
                    ack->setIsRegistration(false);         // Not a registration
                    ack->setIsProbe(false);                // Just a confirmation
                    send(ack, "portOut", arrivalGateIndex); // Send ACK back to sender
                    }
        }

        return;
    }

    // Next check: is destination a VNF inside an NFVI node?
    auto nfviIt = ipToNfviNodeGate.find(destIp);
    if (nfviIt != ipToNfviNodeGate.end()) {
        int nfviGate = nfviIt->second;
        send(pkt, "portOut", nfviGate);
        EV << "Forwarded packet to VNF IP " << destIp << " via toNfviNodes[" << nfviGate << "]\n";
        // Send ACK back to sender
        if(pkt){

            if(pkt->isProbe()){

                   Packet *ack = new Packet("PacketForwardedAck");
                   ack->setSourceAddress(destIp);
                   ack->setDestinationAddress(pkt->getSourceAddress());
                   ack->setIsRegistration(false);
                   ack->setIsProbe(false);
                   send(ack, "portOut", arrivalGateIndex);
                   EV<<"Sent ack"<<endl;
                   }
        }

        return;
    }

    // Unknown destination
    EV_WARN << "Destination IP " << destIp << " unknown. Dropping.\n";
  delete pkt;


}


