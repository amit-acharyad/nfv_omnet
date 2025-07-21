#include <omnetpp.h>
#include <vector>
#include <algorithm> // For std::min_element if you choose to use it
#include "loadbalancer.h"
#include "../messages/packet_m.h" // <--- ADD THIS LINE
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


    int numServerGates = gateSize("outServer"); // Or use the pre-stored numServerGates member variable
    if (numServerGates == 0) {
        EV_WARN << "Module " << getFullPath() << ": No 'outServer' gates defined. Cannot forward packet.\n";
        return; // Or throw an error, depending on your logic
    }
    int chosenGateIndex = currentServerIndex;
    // defensive check if currentServerIndex somehow gets out of sync (optional but good practice)
    if (chosenGateIndex >= numServerGates) {
        chosenGateIndex = 0;
        currentServerIndex = 0; // Reset
    }
    int chosenServerIp;
    currentServerIndex = (currentServerIndex + 1) % numServerGates;
    if (chosenGateIndex < serverIPs.size()) {
         chosenServerIp = serverIPs[chosenGateIndex];

        EV << "Forwarding packet to server IP " << chosenServerIp
           << " via gate outServer[" << chosenGateIndex << "]\n";
    } else {
        EV_ERROR << "Error: chosenGateIndex (" << chosenGateIndex
                 << ") is out of bounds for serverIPs vector (size " << serverIPs.size() << ").\n";
    }
    pkt->setDestinationAddress(chosenServerIp);
    EV << "LoadBalancer: Redirected packet to server IP: " << chosenServerIp
       << ", sending via outServer[" << chosenGateIndex << "]\n";

    send(pkt, "outServer", chosenGateIndex);
}

void Loadbalancer::finish()
{
}
