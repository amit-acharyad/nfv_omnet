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

package omnet_nfv;



network Nfvservicechain
{	
    types:
 channel C extends ned.DatarateChannel {
 datarate = 100Mbps;
 }
    
    submodules:
        client[4]: Client;
        centralSwitch :PacketSwitch{
        numPorts=4;
        }
       // firewall: Firewall;
       // loadBalancer: Loadbalancer;
        //server[2]: Server;
        nfviNode1:Nfvinode{
        id=1;
        cpuCapacity=10000 MIPS;
        memoryCapacity=8192 MB;
        networkBandwidth=1000 Mbps;
        
        }
        nfviNode2: Nfvinode{
        id=2;
        cpuCapacity=10000 MIPS;
        memoryCapacity=8192 MB;
        networkBandwidth=1000 Mbps;
        }
        vnfManager:Vnfmanager;
        nfvo:Nfvo;
    connections allowunconnected:
        for i=0..3 {
//           client[i].out --> firewall.in[i];
//           firewall.out[i] --> loadBalancer.clientIn[i];
//          loadBalancer.clientOut[i] --> firewall.inBack++;
//            firewall.outBack++--> client[i].in;
			  client[i].eth++ <--> C <--> centralSwitch.port++;
			
        }
//        Connect VNF manager to nfvo
        nfvo.vnfMgrGate <--> vnfManager.nfvoGate;
//        connect vnfmanager to nfvinodes

        vnfManager.nfviNodeGate++ <--> nfviNode1.managementGate;
        vnfManager.nfviNodeGate++ <--> nfviNode2.managementGate;
        
       
        nfviNode1.eth++ <--> centralSwitch.port++;
        nfviNode2.eth++ <-->centralSwitch.port++;


    
}
