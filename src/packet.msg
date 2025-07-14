message Packet {
    
    int sourceAddress;
    int destinationAddress;
    bool isRegistration=false;
    bool isProbe;  // to distinguish request vs retry
    

}
