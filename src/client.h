//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#ifndef __OMNET_NFV_CLIENT_H_
#define __OMNET_NFV_CLIENT_H_

#include <omnetpp.h>
using namespace omnetpp;

class Client : public cSimpleModule
{
protected:
    bool awaitingAck = true;         // Whether we are still waiting for acknowledgment
    int maxRetries = 2;              // Optional limit
    int retryCount = 0;
    int destinationIp;


  protected:
    virtual void initialize() override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;

  private:
    cMessage *sendEvent;
    simtime_t sendInterval;
    int packetSize;
};

#endif
