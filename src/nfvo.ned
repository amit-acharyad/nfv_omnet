package omnet_nfv;
simple Nfvo
{
    parameters:
        double placementDelay @unit("ms") =default(100ms);
        int numNfviNodes;
        
    gates:
        input vnfMgrGateIn;
        output vnfMgrGateOut;
        input tenantSwitchIn;
        output tenantSwitchOut;
}
