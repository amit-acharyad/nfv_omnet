
package omnet_nfv;

simple Server 
{	
    parameters:
        int myIpAddress @mutable;
        double cpuConsumptionPerRequest @unit ("MIPS");
        double memoryConsumption @unit("MB");
        double bandwidthConsumption @unit("Mbps");
        
    gates:
        input in;
        
        output out;
}
