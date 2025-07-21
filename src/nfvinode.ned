package omnet_nfv;

simple Nfvinode
{
    parameters:
        int numVnfs=default(10);
        int id;
        int dataPlaneIp;
        double cpuCapacity @unit("MIPS");
        double memoryCapacity @unit("MB");
        double networkBandwidth @unit("Mbps");

    gates:
        input ethIn[] @allowunconnected;
        output ethOut[] @allowunconnected;
        input managementGateIn;
        output managementGateOut;
       	input internalIn[] @display("m=vs");
    	output internalOut[] @display("m=vs");
 
       
}
