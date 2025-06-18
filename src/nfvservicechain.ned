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

package nfv;

network Nfvservicechain
{
    
    submodules:
        client[4]: Client;
        firewall: Firewall;
        loadBalancer: Loadbalancer;
        server[2]: Server;
    connections allowunconnected:
        for i=0..3 {
            client[i].out --> firewall.in[i];
            firewall.out[i] --> loadBalancer.clientIn[i];
            loadBalancer.clientOut[i] --> firewall.inBack++;
            firewall.outBack++--> client[i].in;

        }
        for j=0..1 {
            loadBalancer.serverOut[j] --> server[j].in[0];
            server[j].out[0] --> loadBalancer.serverIn[j];
        }


    
}
