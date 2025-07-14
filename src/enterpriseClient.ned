package omnet_nfv;

simple EnterpriseClient {
    parameters:
        int enterpriseId;
        string serviceChainType;
        int desiredServerCount;
        double requestTime @unit(s);
    gates:
        output out;
        input in;
}

