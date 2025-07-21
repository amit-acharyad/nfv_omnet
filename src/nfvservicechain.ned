package omnet_nfv;
network Nfvservicechain
{
    parameters:
        int numClients = default(4);
        int numNfviNodes = default(2);
        int numEnterpriseClients=default(4);
        int centralSwitchPorts = default(numClients + numNfviNodes);

    types:
        channel C extends ned.DatarateChannel {
            datarate = 100Mbps;
        }
    submodules:
        client[numClients]: Client {
            parameters:
                sourceAddress = index + 1;
                
destinationAddress = 
            (index % 4 == 0) ? 102 :
            (index % 4 == 1) ? 106 :
            (index % 4 == 2) ? 109 :
                               113;        }
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
        nfvo: Nfvo{
        parameters:
           numNfviNodes= parent.numNfviNodes;
        };
        enterpriseClients[numEnterpriseClients]:EnterpriseClient{
        parameters:
         enterpriseId=index;
         serviceChainType="Firewall->LoadBalancer->Server";
         desiredServerCount=1+index%2;
         requestTime =2 s ;
       
        };
        tenantSwitch:TenantSwitch{
        parameters:
        	numTenants=parent.numEnterpriseClients;
        }

    connections allowunconnected:
        //connect clients and centralpacketswitch
        for i = 0..numClients - 1 {
            
            client[i].ethOut --> C--> centralSwitch.portIn[i];
            centralSwitch.portOut[i]-->C--> client[i].ethIn;
        }

        // Connect VNF manager to NFVO
        
        nfvo.vnfMgrGateOut-->vnfManager.nfvoGateIn;
        vnfManager.nfvoGateOut -->nfvo.vnfMgrGateIn;

        // Connect VNF Manager to NFVI Nodes
        for i = 0..numNfviNodes - 1 {
            vnfManager.nfviNodeGateOut++ --> nfviNode[i].managementGateIn;
            nfviNode[i].managementGateOut --> vnfManager.nfviNodeGateIn++;
        }

        // Connect NFVI Nodes to central switch
        for i = 0..numNfviNodes - 1 {
           nfviNode[i].ethOut++ --> C --> centralSwitch.portIn[numClients+i];
           centralSwitch.portOut[numClients+i] --> C--> nfviNode[i].ethIn++;
           
        }
        
        //Connect Enterprise clinets to tenantSwitch 
        for i =0..numEnterpriseClients-1{
        	enterpriseClients[i].out --> C-->tenantSwitch.fromTenants[i];
        	tenantSwitch.toTenants[i] --> C--> enterpriseClients[i].in;
        }
        //connect tenant switch to nfvo
        tenantSwitch.toNfvo --> C --> nfvo.tenantSwitchIn;
        nfvo.tenantSwitchOut --> C --> tenantSwitch.fromNfvo;
        
        
        
}
