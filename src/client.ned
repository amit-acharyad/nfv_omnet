package omnet_nfv;
simple Client
{
    parameters:
        double sendInterval @unit(s)=default(3s);
        int sourceAddress;//source Ip
   
        
    gates:
        input ethIn;
        output ethOut;
}


