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
using namespace omnetpp;
Define_Module(Firewall);

void Firewall::handleMessage(cMessage *msg)  {
        // Cast to Packet (optional, but good for type awareness)
        Packet *pkt = dynamic_cast<Packet*>(msg);
        if (!pkt) {
            EV << "Firewall received a non-Packet message, forwarding anyway: " << msg->getName() << "\n";
        }


        //Simulate some delay
        scheduleAt(simTime()+0.001,msg);
        pkt->setDestinationAddress(loadBalancerVIP);//Redirect to load baalncer VNF
        EV<<"Firewall redirected packet to loadbalancer VIP"<<loadBalancerVIP<<endl;
        send(pkt,"out");

    }


void Firewall::initialize(){
    EV<<"Firewall: Initialied"<<endl;
    loadBalancerVIP=par("loadBalancerVIP").intValue();
    EV<<"Firewall: COnfigure with loadbalancer VIP:"<<loadBalancerVIP<<endl;

}


