#include "nfvinode.h"
#include "../messages/nfvMessages_m.h"
#include "firewall.h"
#include "loadbalancer.h"
#include "server.h"
#include <cstring>
#include "../messages/packet_m.h"
#include <queue>
#include "../messages/vnfRegistration_m.h"


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
}
int Nfvinode::getEnterpriseIdForVnfIp(int ip) {
    return vnfIpToEnterpriseId.count(ip) ? vnfIpToEnterpriseId[ip] : -1;
}

void Nfvinode::handleMessage(cMessage *msg)
{
    // 1. Deployment request
    if (auto* vnfRequest = dynamic_cast<VnfDeploymentRequest*>(msg)) {
        handleVnfDeploymentRequest(vnfRequest);
        return;
    }

    // 2. Trigger wiring event
    if (strcmp(msg->getName(), "TriggerWiring") == 0) {
        int enterpriseId = msg->par("enterpriseId").longValue();
        EV << "NFVINode[" << getId() << "]: Received wiring trigger for Enterprise ID " << enterpriseId << "\n";
        wireInternalServiceChain(enterpriseId);
        delete msg;
        return;
    }

    // 3. Data packet – fully handled in one place
    if (auto* packet = dynamic_cast<Packet*>(msg)) {
        handleDataPacket(packet, msg->getArrivalGate());
        return;
    }

    // 4. Unknown message
    EV_WARN << "NFVINode[" << getId() << "]: Unknown message type: " << msg->getName() << "\n";
    delete msg;
}



void Nfvinode::handleVnfDeploymentRequest(VnfDeploymentRequest *req)
{
    EV << "NFVINode[" << getId() << "]: Received VNF Deployment Request for " << req->getVnfName()
       << " (Type: " << req->getVnfType() << ", IP: " << req->getVnfIpAddress() << ")" << endl;

    VnfDeploymentResponse *response = new VnfDeploymentResponse("VnfDeploymentResponse");
    response->setVnfName(req->getVnfName());
    response->setDeployedVnfIp(0); // Default to 0, set on success
    response->setRequestId(req->getRequestId());
    response->setNfviNodeId(req->getNfviNodeId());
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
    cModule* vnfModule = vnfModuleType->create(req->getVnfName(), this);


    vnfModule->buildInside();

    // Set common parameters
    vnfModule->par("myIpAddress").setIntValue(req->getVnfIpAddress());

    // Set VNF-specific parameters
    if (req->getVnfType() == VNF_TYPE_FIREWALL) {
        vnfModule->par("loadBalancerVIP").setIntValue(req->getFirewallLbVip());
    }
    else if (req->getVnfType() == VNF_TYPE_LOADBALANCER) {
        // 1. Collect already deployed server IPs
        std::vector<int> backendServerIps;
        for (const auto& [ip, vnf] : deployedVnfsByIp) {
            if (vnf.type == VNF_TYPE_SERVER) {
                backendServerIps.push_back(ip);
            }
        }

        // 2. If no servers exist, skip LB deployment
        if (backendServerIps.empty()) {
            EV_WARN << "NFVINode[" << getId() << "]: No backend servers found. Skipping LoadBalancer deployment." << endl;
            delete req;
            return;  // Exit without deploying LB
        }
            // 3. Cast to Loadbalancer* and directly assign vector
        Loadbalancer* lb = dynamic_cast<Loadbalancer*>(vnfModule);
        if (lb == nullptr) {
            EV_ERROR << "NFVINode: Could not cast " << req->getVnfName()
                     << " to Loadbalancer*. Check module type and class.\n";
            delete req;
            return;
        }
        lb->setBackendServerIps(backendServerIps);

            EV << "NFVINode[" << getId() << "]: Initialized LoadBalancer with "
               << backendServerIps.size() << " backend servers.\n";
    }


    vnfModule->callInitialize();

    // Update resource accounting
    availableCpu -= req->getCpuRequest();
    availableMemory -= req->getMemoryRequest();
    availableBandwidth -= req->getBandwidthRequest();


    DeployedVnfModule deployed;
    deployed.name = req->getVnfName();
    deployed.type = req->getVnfType();
    deployed.ipAddress = req->getVnfIpAddress();
    deployed.moduleRef = vnfModule;  // your dynamically created module

    // Store in per-enterprise service chain
    int enterpriseId = req->getRequestId();
    serviceChains[enterpriseId].enterpriseId = enterpriseId;
    serviceChains[enterpriseId].vnfsOrdered.push_back(deployed);

    // (Optional) global index by IP for data packet routing
    deployedVnfsByIp[deployed.ipAddress] = deployed;
    vnfIpToEnterpriseId[req->getVnfIpAddress()] = enterpriseId;

    // Send success response
    response->setSuccess(true);
    response->setInfoMessage("VNF deployed successfully");
    response->setDeployedVnfIp(req->getVnfIpAddress());

    EV << "NFVINode[" << getId() << "]: Successfully deployed " << req->getVnfName()
       << " with IP " << req->getVnfIpAddress() << ". Remaining Resources (CPU: " << availableCpu
       << ", Mem: " << availableMemory << ", BW: " << availableBandwidth << ")" << endl;

    send(response, "managementGateOut");
    if (req->getVnfType() == VNF_TYPE_FIREWALL) {
        VnfRegistrationMessage *reg = new VnfRegistrationMessage();
        reg->setVnfIp(req->getVnfIpAddress());
        reg->setEnterpriseId(req->getRequestId());
        reg->setNfviNodeId(this->getId());  // or your NFVI node ID
        send(reg, "ethOut",0);
    }

    delete req;
}


void Nfvinode::handleDataPacket(Packet *packet, cGate *arrivalGate)
{
    int dstIp = packet->getDestinationAddress();
    std::string gateName = arrivalGate->getName();

    EV << "NFVINode[" << getId() << "]: Packet arrived at gate: " << gateName << " destined for IP: " << dstIp << "\n";

    if (gateName == "internalIn") {
        // Internal reply → forward to external network
        EV << "NFVINode[" << getId() << "]: Packet from internal VNF → sending to ethOut\n";
        send(packet, "ethOut", 0);
        return;
    }

    if (gateName == "ethIn") {
        int enterpriseId = getEnterpriseIdForVnfIp(dstIp);

        if (serviceChains.count(enterpriseId) == 0) {
            EV_WARN << "Unknown enterpriseId for IP " << dstIp << ". Dropping.\n";
            delete packet;
            return;
        }

        if (!serviceChains[enterpriseId].wiringDone) {
            EV << "Wiring not done yet → buffering packet\n";
            bufferedPacketsPerEnterprise[enterpriseId].push(packet);
            return;
        }

        for (const auto& [ip, vnf] : deployedVnfsByIp) {
            // Check if it's a firewall AND if its IP matches the packet's destination
            if (vnf.type == VNF_TYPE_FIREWALL && ip == dstIp) {
                int gateNo = vnfIpToInternalGateIndex[ip];
                send(packet, "internalOut", gateNo);
                EV << "Forwarded to Firewall (matching IP " << vnf.name << "): " << dstIp << "\n";
                return; // Packet sent, exit the loop/function
            }
        }


        EV_WARN << "No Firewall found. Dropping packet.\n";
        delete packet;
        return;
    }

    // Case: packet from VNF to another VNF or outside
    auto it = deployedVnfsByIp.find(dstIp);
    if (it != deployedVnfsByIp.end()) {
        // Internal delivery to next VNF
        send(packet, it->second.moduleRef->gate("in"));
        EV << "Forwarded internally to VNF: " << it->second.name << "\n";
    } else {
        // Outgoing delivery
        send(packet, "ethOut", 0);
        EV << "Destination not internal → Sent to external network\n";
    }
}




void Nfvinode::wireInternalServiceChain(int enterpriseId) {
    auto it = serviceChains.find(enterpriseId);
    if (it == serviceChains.end() || it->second.wiringDone)
        return;

    const auto& chain = it->second.vnfsOrdered;
    if (chain.empty()) {
        EV_WARN << "NFVINode[" << getId() << "]: No VNFs to wire for enterprise " << enterpriseId << "\n";
        return;
    }

    cModule* firewall = nullptr;
    cModule* loadBalancer = nullptr;
    std::vector<cModule*> servers;

    // Identify modules
    for (const auto& vnf : chain) {
        switch (vnf.type) {
            case VNF_TYPE_FIREWALL:
                firewall = vnf.moduleRef;
                break;
            case VNF_TYPE_LOADBALANCER:
                loadBalancer = vnf.moduleRef;
                break;
            case VNF_TYPE_SERVER:
                servers.push_back(vnf.moduleRef);
                break;
            default:
                break;
        }
    }
    int gateIndex;
    int firewallIp = -1;
    for (const auto& vnf : serviceChains[enterpriseId].vnfsOrdered) {
        if (vnf.type == VNF_TYPE_FIREWALL) {
            firewallIp = vnf.ipAddress;
            break;
        }
    }
    if (firewallIp == -1) {
        EV_ERROR << "No firewall found for enterprise " << enterpriseId << "\n";
        return;
    }


    auto its = vnfIpToInternalGateIndex.find(firewallIp);
    if (its == vnfIpToInternalGateIndex.end()) {
        gateIndex = nextAvailableGateIndex++;
        vnfIpToInternalGateIndex[firewallIp] = gateIndex;

        if (gateSize("internalOut") <= gateIndex) {
            setGateSize("internalOut", gateIndex + 1);
        }
        if (gateSize("internalIn") <= gateIndex) {
            setGateSize("internalIn", gateIndex + 1);
        }
    } else {
        gateIndex = its->second;
    }

    // Now you can safely connect:
    if (firewall && hasGate("internalOut") && firewall->hasGate("in")) {
        gate("internalOut", gateIndex)->connectTo(firewall->gate("in"));
        firewall->gate("out")->connectTo(gate("internalIn",gateIndex));

        EV << "Connected internalOut and internal in  [" << gateIndex << "] → Firewall.in and firewall out for enterprise " << enterpriseId << "\n";
    }

    // Firewall ↔ LoadBalancer
    if (firewall && loadBalancer) {
        firewall->gate("outLB")->connectTo(loadBalancer->gate("in"));
        loadBalancer->gate("out")->connectTo(firewall->gate("inLB"));

        EV << "Connected Firewall.outLB ↔ LoadBalancer.in (bidirectional)\n";
    }

    // LoadBalancer ↔ Servers (multi-gate)
    if (loadBalancer && !servers.empty()) {
        int numServers = servers.size();
        loadBalancer->setGateSize("outServer", numServers);
        loadBalancer->setGateSize("inServer", numServers);

        for (int i = 0; i < numServers; ++i) {
            cModule* server = servers[i];
            if (!server) continue;

            loadBalancer->gate("outServer", i)->connectTo(server->gate("in"));
            server->gate("out")->connectTo(loadBalancer->gate("inServer", i));
            EV << "Connected LoadBalancer.outServer[" << i << "] ↔ " << server->getName() << ".in (bidirectional)\n";
        }
    }



    it->second.wiringDone = true;

    // Replay buffered packets
    auto& queue = bufferedPacketsPerEnterprise[enterpriseId];
    while (!queue.empty()) {
        Packet* pkt = queue.front();
        queue.pop();
        handleDataPacket(pkt, pkt->getArrivalGate());
    }

    EV << "✅ Wired full internal service chain for enterprise " << enterpriseId << "\n";
}


