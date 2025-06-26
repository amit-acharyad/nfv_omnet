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

#include "nfvinode.h"
#include "nfvMessages_m.h"
#include "firewall.h"
#include "loadbalancer.h"
#include "server.h"
#include <cstring>
#include "packet_m.h"

Define_Module(Nfvinode);

void Nfvinode::initialize()
{
    EV << "NFVINode[" << getId() << "]: Initializing." << endl;
    dataPlaneIp = par("dataPlaneIp").intValue();
    totalCpuCapacity = par("cpuCapacity").doubleValue(); // Get as double
    totalMemoryCapacity = par("memoryCapacity").doubleValue(); // Get as double
    totalNetworkBandwidth = par("networkBandwidth").doubleValue(); // Get as double

    availableCpu = totalCpuCapacity;
    availableMemory = totalMemoryCapacity;
    availableBandwidth = totalNetworkBandwidth;

    vnfIdCounter = 0; // Initialize VNF ID counter

    EV << "NFVINode " << getId() << " Initialized with capacities: CPU=" << totalCpuCapacity
       << " MEM=" << totalMemoryCapacity << " BW=" << totalNetworkBandwidth << endl;
    EV << "NFVINode[" << getId() << "]: My Data Plane IP: " << dataPlaneIp << endl;

    EV<<"Registering port"<<endl;
    int myIp = par("dataPlaneIp").intValue();  // or store it in a member variable

        Packet *reg = new Packet("Register");
        reg->setSourceAddress(myIp);
        reg->setIsRegistration(true);
        send(reg, "ethOut", 0);  // assuming 1 ethOut per node, index 0
}

void Nfvinode::handleMessage(cMessage *msg)
{
    // Check if it's a management message (VnfDeploymentRequest)
    VnfDeploymentRequest* vnfRequest = dynamic_cast<VnfDeploymentRequest*>(msg);
    if (vnfRequest) {
        handleVnfDeploymentRequest(vnfRequest);
        return;
    }

    // Check if it's a data plane packet
    Packet* packet = dynamic_cast<Packet*>(msg);
    if (packet) {
        handleDataPacket(packet, msg->getArrivalGate());
        return;
    }

    // If it's neither, delete it
    EV_WARN << "NFVINode[" << getId() << "]: Received unhandled message of type " << msg->getClassName() << ": " << msg->getName() << endl;
    delete msg;
}
/*
void Nfvinode::handleVnfDeploymentRequest(VnfDeploymentRequest *req)
{
    EV << "NFVINode[" << getId() << "]: Received VNF Deployment Request for " << req->getVnfName()
       << " (Type: " << req->getVnfType() << ", IP: " << req->getVnfIpAddress() << ")" << endl;

    VnfDeploymentResponse *response = new VnfDeploymentResponse("VnfDeploymentResponse");
    response->setVnfName(req->getVnfName());
    response->setDeployedVnfIp(0); // Default to 0, set on success
    response->setRequestId(req->getRequestId());

    // Resource availability check
    if (req->getCpuRequest() > availableCpu ||
        req->getMemoryRequest() > availableMemory ||
        req->getBandwidthRequest() > availableBandwidth)
    {
        response->setSuccess(false);
        response->setInfoMessage("Insufficient resources");
        EV_WARN << "NFVINode[" << getId() << "]: Deployment failed for " << req->getVnfName() << ": Insufficient resources." << endl;
        send(response, "managementGateOut");
        delete req;
        return;
    }

    // Determine VNF module type
    cModuleType* vnfType = nullptr;
    switch (req->getVnfType()) {
        case VNF_TYPE_FIREWALL:
            vnfType = cModuleType::get("omnet_nfv.Firewall");
            break;
        case VNF_TYPE_LOADBALANCER:
            vnfType = cModuleType::get("omnet_nfv.LoadBalancer");
            break;
        case VNF_TYPE_SERVER:
            vnfType = cModuleType::get("omnet_nfv.Server");
            break;
        default:
            response->setSuccess(false);
            response->setInfoMessage("Unknown VNF type");
            EV_ERROR << "NFVINode[" << getId() << "]: Unknown VNF type requested: " << req->getVnfType() << endl;
            send(response, "managementGateOut");
            delete req;
            return;
    }

    // Create the VNF module dynamically
    std::string vnfModuleName = req->getVnfName();
    // Declare and create the module
    cModule* vnfModule = nullptr;
    vnfModule = vnfType->create(vnfModuleName.c_str(), this, vnfIdCounter++);
    vnfModule->buildInside();

    // Set parameters
    vnfModule->par("myIpAddress").setIntValue(req->getVnfIpAddress());

    if (req->getVnfType() == VNF_TYPE_FIREWALL) {
        vnfModule->par("loadBalancerVIP").setIntValue(req->getFirewallLbVip());
    }
    else if (req->getVnfType() == VNF_TYPE_LOADBALANCER) {
        std::stringstream ipList;
        for (int i = 0; i < req->getBackendServerIpsArraySize(); ++i) {
            if (i > 0) ipList << ",";
            ipList << req->getBackendServerIps(i);
        }
        vnfModule->par("serverIPs").setStringValue(ipList.str().c_str());
    }

    vnfModule->callInitialize();


    // Update resource usage
    availableCpu -= req->getCpuRequest();
    availableMemory -= req->getMemoryRequest();
    availableBandwidth -= req->getBandwidthRequest();

    // Store reference to deployed module
    DeployedVnfModule deployedVnf;
    deployedVnf.name = req->getVnfName();
    deployedVnf.type = req->getVnfType();
    deployedVnf.ipAddress = req->getVnfIpAddress();
    deployedVnf.moduleRef = vnfModule;

    deployedVnfsByIp[deployedVnf.ipAddress] = deployedVnf;
    deployedVnfsByName[deployedVnf.name] = deployedVnf;

    // Respond to manager
    response->setSuccess(true);
    response->setInfoMessage("VNF deployed successfully");
    response->setDeployedVnfIp(req->getVnfIpAddress());

    EV << "NFVINode[" << getId() << "]: Successfully deployed " << req->getVnfName()
       << " with IP " << req->getVnfIpAddress() << ". Remaining Resources (CPU: " << availableCpu
       << ", Mem: " << availableMemory << ", BW: " << availableBandwidth << ")" << endl;

    send(response, "managementGateOut");
    delete req;
}*/
void Nfvinode::handleVnfDeploymentRequest(VnfDeploymentRequest *req)
{
    EV << "NFVINode[" << getId() << "]: Received VNF Deployment Request for " << req->getVnfName()
       << " (Type: " << req->getVnfType() << ", IP: " << req->getVnfIpAddress() << ")" << endl;

    VnfDeploymentResponse *response = new VnfDeploymentResponse("VnfDeploymentResponse");
    response->setVnfName(req->getVnfName());
    response->setDeployedVnfIp(0); // Default to 0, set on success
    response->setRequestId(req->getRequestId());

    // Check resource availability
    if (req->getCpuRequest() > availableCpu ||
        req->getMemoryRequest() > availableMemory ||
        req->getBandwidthRequest() > availableBandwidth)
    {
        response->setSuccess(false);
        response->setInfoMessage("Insufficient resources");
        EV_WARN << "NFVINode[" << getId() << "]: Deployment failed for " << req->getVnfName()
                << ": Insufficient resources." << endl;
        send(response, "managementGateOut");
        delete req;
        return;
    }

    // Determine module type name string for creation
    const char* vnfTypeName = nullptr;
    switch (req->getVnfType()) {
        case VNF_TYPE_FIREWALL:
            vnfTypeName = "omnet_nfv.Firewall";
            break;
        case VNF_TYPE_LOADBALANCER:
            vnfTypeName = "omnet_nfv.Loadbalancer";
            break;
        case VNF_TYPE_SERVER:
            vnfTypeName = "omnet_nfv.Server";
            break;
        default:
            response->setSuccess(false);
            response->setInfoMessage("Unknown VNF type");
            EV_ERROR << "NFVINode[" << getId() << "]: Unknown VNF type requested: " << req->getVnfType() << endl;
            send(response, "managementGateOut");
            delete req;
            return;
    }

    // Check if there is room in vnf[] vector to deploy another VNF
    if (vnfIdCounter >= par("numVnfs").intValue()) {
        response->setSuccess(false);
        response->setInfoMessage("No capacity to deploy more VNFs");
        EV_WARN << "NFVINode[" << getId() << "]: Deployment failed for " << req->getVnfName()
                << ": Capacity full." << endl;
        send(response, "managementGateOut");
        delete req;
        return;
    }

    // Create module inside vnf[] vector at index vnfIdCounter
    int idx = vnfIdCounter++;
    cModuleType* vnfModuleType = cModuleType::get(vnfTypeName);
    cModule* vnfModule = vnfModuleType->create("vnf", this);

    // Optionally set the module name to the requested VNF name
    vnfModule->setName(req->getVnfName());

    vnfModule->buildInside();

    // Set common parameters
    vnfModule->par("myIpAddress").setIntValue(req->getVnfIpAddress());

    // Set VNF-specific parameters
    if (req->getVnfType() == VNF_TYPE_FIREWALL) {
        vnfModule->par("loadBalancerVIP").setIntValue(req->getFirewallLbVip());
    }
    else if (req->getVnfType() == VNF_TYPE_LOADBALANCER) {
        std::stringstream ipList;
        for (int i = 0; i < req->getBackendServerIpsArraySize(); ++i) {
            if (i > 0) ipList << ",";
            ipList << req->getBackendServerIps(i);
        }
        vnfModule->par("serverIPs").setStringValue(ipList.str().c_str());
    }

    vnfModule->callInitialize();

    // Update resource accounting
    availableCpu -= req->getCpuRequest();
    availableMemory -= req->getMemoryRequest();
    availableBandwidth -= req->getBandwidthRequest();

    // Store deployed VNF info
    DeployedVnfModule deployedVnf;
    deployedVnf.name = req->getVnfName();
    deployedVnf.type = req->getVnfType();
    deployedVnf.ipAddress = req->getVnfIpAddress();
    deployedVnf.moduleRef = vnfModule;

    deployedVnfsByIp[deployedVnf.ipAddress] = deployedVnf;
    deployedVnfsByName[deployedVnf.name] = deployedVnf;

    // Send success response
    response->setSuccess(true);
    response->setInfoMessage("VNF deployed successfully");
    response->setDeployedVnfIp(req->getVnfIpAddress());

    EV << "NFVINode[" << getId() << "]: Successfully deployed " << req->getVnfName()
       << " with IP " << req->getVnfIpAddress() << ". Remaining Resources (CPU: " << availableCpu
       << ", Mem: " << availableMemory << ", BW: " << availableBandwidth << ")" << endl;

    send(response, "managementGateOut");
    delete req;
}


void Nfvinode::handleDataPacket(Packet *packet, cGate *arrivalGate)
{
    int destinationIp = packet->getDestinationAddress();
    EV << "NFVINode[" << getId() << "]: Received data packet (Src: " << packet->getSourceAddress()
       << ", Dst: " << destinationIp << ") on gate " << arrivalGate->getFullName() << endl;

    // --- Internal Routing Logic within NFVINode ---

    // 1. Packet from external (PacketSwitch) destined for an internal VNF
    // (e.g., Client -> PacketSwitch -> NFVINode -> Firewall)
    if (arrivalGate->isName("ethIn") || arrivalGate->isName("ethOut")) { // Changed from "eth" to "ethg" as per NED
        auto it = deployedVnfsByIp.find(destinationIp);
        EV<<"Before checking it ne"<<it->second.ipAddress<<endl;



        if (it != deployedVnfsByIp.end()) {
            // Destination IP matches an internal VNF
            EV<<"Before assigning module ref"<< it->second.name<<"Modref"<<it->second.type<<"modRed"<<it->second.moduleRef<<endl;
            cModule* targetVnfModule = it->second.moduleRef;
            // Assuming VNFs have an 'in' gate for data packets
            EV<<"TargetVNF has"<<targetVnfModule->gateCount()<<"name"<<targetVnfModule->getDisplayName()<<endl;
            send(packet, targetVnfModule->gate("in"));
            EV << "NFVINode[" << getId() << "]: Forwarded packet to internal VNF: "
               << targetVnfModule->getName() << " (IP: " << destinationIp << ")" << endl;
        } else {
            // Destination IP is not an internal VNF. This might be an error or
            // implies cross-NFVINode routing which we'll handle later.
            EV_WARN << "NFVINode[" << getId() << "]: Packet to IP " << destinationIp
                    << " not found among internal VNFs. Dropping." << endl;
            delete packet;
        }
    }
    // 2. Packet from an internal VNF, looking for next hop
    // (e.g., Firewall -> NFVINode -> LoadBalancer, OR WebServerVNF -> NFVINode -> PacketSwitch)
    else { // Packet came from an internal VNF (its 'out' gate)
        // Find which VNF sent this packet
        cModule* senderVnfModule = arrivalGate->getOwnerModule();
        EV << "NFVINode[" << getId() << "]: Packet from internal VNF: " << senderVnfModule->getName() << endl;

        // Check if destination is another internal VNF on this node
        auto it = deployedVnfsByIp.find(destinationIp);
        if (it != deployedVnfsByIp.end()) {
            // Destination IP matches another internal VNF on this node
            cModule* targetVnfModule = it->second.moduleRef;
            // Packet goes from senderVnfModule.out -> NFVINode.in -> NFVINode internal logic -> targetVnfModule.in
            send(packet, targetVnfModule->gate("in")); // Send to the 'in' gate of the NEXT VNF
            EV << "NFVINode[" << getId() << "]: Forwarded packet internally from "
               << senderVnfModule->getName() << " to " << targetVnfModule->getName()
               << " (IP: " << destinationIp << ")" << endl;
        } else {
            // Destination IP is NOT an internal VNF. It must be external (e.g., a Client)
            // Send it back out to the PacketSwitch.
            // This assumes ethg[0] is the main data plane connection to the switch.
            send(packet, "ethOut", 0); // Correct gate name: "ethg" (from NFVINode.ned)
            EV << "NFVINode[" << getId() << "]: Forwarded packet to external network (PacketSwitch) for IP: " << destinationIp << endl;
        }
    }
}





