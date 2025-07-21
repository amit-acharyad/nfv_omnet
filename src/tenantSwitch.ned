package omnet_nfv;
simple TenantSwitch
{	
    parameters:
        int numTenants;
    gates:
        input fromTenants[numTenants];   // From enterprise clients
        input fromNfvo;        // From NFVO
        output toTenants[numTenants];    // To enterprise clients
        output toNfvo;         // To NFVO
}

