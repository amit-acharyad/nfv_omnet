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
#include "packet_m.h"
#include "firewall.h"
#include <cstring>
using namespace omnetpp;
Define_Module(Firewall);

void Firewall::handleMessage(cMessage *msg) {
    auto *pkt = dynamic_cast<Packet*>(msg);
    EV<<"Packet received in firewall"<<pkt->getDestinationAddress()<<endl;
    if(strcmp(msg->getArrivalGate()->getName(),"in")==0){
        // You could inspect packet here
            pkt->setDestinationAddress(loadBalancerVIP);  // LB IP set during deployment

            send(pkt, "outLB");  // outLB goes to NFVINode
            return;
    }
    else if (strcmp(msg->getArrivalGate()->getName(),"inLB")==0){
        EV<<"Sending respose coming from inLB to out to destination "<<pkt->getDestinationAddress()<<endl;
        send(pkt,"out");
    }

}



void Firewall::initialize(){
    EV<<"Firewall: Initialied"<<endl;
    loadBalancerVIP=par("loadBalancerVIP").intValue();
    EV<<"Firewall: COnfigure with loadbalancer VIP:"<<loadBalancerVIP<<endl;

}


