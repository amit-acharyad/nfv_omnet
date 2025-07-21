
#ifndef __OMNET_NFV_SERVER_H_
#define __OMNET_NFV_SERVER_H_

#include <omnetpp.h>

using namespace omnetpp;


class Server : public cSimpleModule
{
  protected:
    int myIpAddress;
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish()override;
};

#endif
