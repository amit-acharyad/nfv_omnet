#ifndef __OMNET_NFV_LOADBALANCER_H_
#define __OMNET_NFV_LOADBALANCER_H_

#include <omnetpp.h>
#include <vector>
using namespace omnetpp;

class Loadbalancer : public cSimpleModule
{
  protected:
    std::vector<int> serverIPs;//list of servervnfs
    int currentServerIndex;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish()override;
  public:
    void setBackendServerIps(const std::vector<int>& ips) {
            serverIPs = ips;
        }
};

#endif
