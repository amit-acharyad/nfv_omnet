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
    parameters:
        int numClients = default(4);
        int numNfviNodes = default(2);
        int centralSwitchPorts = default(numClients + numNfviNodes);

    types:
        channel C extends ned.DatarateChannel {
            datarate = 100Mbps;
        }
    submodules:
        client[numClients]: Client {
            parameters:
                clientId = index + 1;
                targetVnfIp = 100; // Firewalls external IP
        }
        centralSwitch: PacketSwitch {
            parameters:
                numPorts = parent.centralSwitchPorts;
        }
        nfviNode[numNfviNodes]: Nfvinode {
            parameters:
                dataPlaneIp = 10 + index;
                cpuCapacity = 10000 MIPS;
                memoryCapacity = 8192 MB;
                networkBandwidth = 1000 Mbps;
        }
        vnfManager: Vnfmanager;
        nfvo: Nfvo;

    connections allowunconnected:
        for i = 0..numClients - 1 {
            client[i].eth <--> C <--> centralSwitch.port[i];
        }

        // Connect VNF manager to NFVO
        nfvo.vnfMgrGate <--> vnfManager.nfvoGate;

        // Connect VNF Manager to NFVI Nodes
        for i = 0..numNfviNodes - 1 {
            vnfManager.nfviNodeGate++ <--> nfviNode[i].managementGate;
        }

        // Connect NFVI Nodes to central switch
        for i = 0..numNfviNodes - 1 {
            nfviNode[i].eth++ <--> C <--> centralSwitch.port[numClients + i];
        }
}
