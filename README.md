## Project Overview

This project implements a Network Functions Virtualization (NFV) service chain simulation using OMNeT++. It demonstrates the dynamic deployment of Virtual Network Functions (VNFs) on Network Function Virtualization Infrastructure (NFVI) nodes and the subsequent routing of client traffic through a defined service chain, including a Firewall, a Load Balancer, and multiple Web Servers.

The simulation models the interaction between the Management and Orchestration (MANO) plane (NFVO, VNFManager) and the Data Plane (Clients, PacketSwitch, NFVINodes, VNFs). It also implements per-enterprise service chain isolation, dynamic internal gate indexing, and internal routing based on IP-to-gate mapping.

## Key Features

* **Enterprise-Tenant-Aware Chain Requests:** Enterprises (clients) request service chains via TenantSwitch to the NFVO, which triggers VNF deployment.
* **Dynamic NFVI Node Deployment:** Easily configure the number of NFVI nodes in the network.
* **VNF Deployment & Lifecycle:**

  * `VnfManager` sends deployment requests to `NFVINode`s.
  * `NFVINode`s dynamically instantiate VNFs (Firewall, LoadBalancer, WebServerVNF) as submodules.
  * Each enterprise gets its own isolated VNF chain.
* **Simplified IP-based Routing:**

  * Packets are enhanced with `sourceAddress` and `destinationAddress` (simplified integer IPs).
  * `PacketSwitch` routes packets based on destination IP using a configurable routing table.
* **Network Service Chaining (Firewall, LoadBalancer, WebServerVNF):**

  * **Firewall VNF:** Receives traffic, (conceptually) applies filtering rules, and forwards it to the Load Balancer's VIP.
  * **LoadBalancer VNF:** Distributes incoming requests across multiple backend `WebServerVNF` instances using a round-robin algorithm.
  * **WebServerVNF:** Receives requests and generates corresponding responses, sending them back to the client.
* **Internal NFVINode Routing:**

  * Each enterprise gets a unique `internalOut[]` and `internalIn[]` gate pair for isolation.
  * The NFVINode routes packets internally using per-enterprise gate indices and IP-to-gate mappings.
  * Bi-directional flows are supported with responses taking the reverse path through the chain.
* **Request-Response Flow:** Simulates a complete communication cycle from client request to server response and back.

## Modules

The simulation is built using the following custom OMNeT++ modules:

* **`Client`**: Generates and sends data packets (requests) to the network, includes retry and response tracking logic.
* **`TenantSwitch`**: Forwards enterprise chain requests to the NFVO based on client initiation.
* **`PacketSwitch`**: Acts as a central network switch, forwarding packets based on destination IP.
* **`NFVINode`**: Represents a physical server capable of hosting VNFs. It manages resource allocation, internal wiring, and traffic routing.
* **`VnfManager`**: Part of the MANO plane, responsible for sending VNF deployment requests to `NFVINode`s.
* **`NFVO` (Network Function Virtualization Orchestrator)**: The top-level orchestrator responsible for receiving chain requests, triggering deployment, and wiring.
* **`Firewall` (VNF)**: Entry point of the service chain, filters and forwards traffic.
* **`LoadBalancer` (VNF)**: Distributes requests to WebServerVNFs.
* **`WebServerVNF` (VNF)**: Processes client requests and sends responses.

## Prerequisites

* **OMNeT++ 6.0 or higher:** This project is built and tested with OMNeT++ 6.x.
* A C++ compiler (usually part of the OMNeT++ installation).

## Setup and Installation

1. **Clone the repository:**

   ```bash
   git clone <repository_url>
   cd <project_directory>
   ```
2. **Open in OMNeT++ IDE:**

   * Launch OMNeT++ IDE.
   * Go to `File -> Open Projects from File System...`.
   * Browse to the root directory of this project and click `Finish`.
3. **Build the project:**

   * In the OMNeT++ IDE, right-click on the project in the Project Explorer.
   * Select `Build Project`. This will compile all C++ code and generate necessary files from `.ned` and `.msg` files.

## Usage

1. **Configure Simulation:**

   * Open `omnetpp.ini`. You can adjust parameters like `numClients`, `numNfviNodes`, and specific VNF IPs here.
   * Example:

     ```ini
     [General]
     network = Nfvservicechain

     Nfvservicechain.numClients = 4
     Nfvservicechain.numNfviNodes = 2
     ```
2. **Run the Simulation:**

   * In the OMNeT++ IDE, right-click on `Nfvservicechain.ned`.
   * Select `Run As -> OMNeT++ Simulation`.
   * Observe the GUI and console for flow of messages and logs.

## Simulation Scenario

A typical simulation run now includes:

1. **Initialization:** `NFVO` and `VnfManager` initialize. `NFVINode`s come online.
2. **Enterprise Request Trigger:** Enterprise clients generate service chain requests that are forwarded by the `TenantSwitch` to the `NFVO`.
3. **VNF Deployment:** The `VnfManager` deploys VNFs (Firewall, LoadBalancer, WebServers) to selected `NFVINode`s.
4. **Internal Service Chain Wiring:**

   * After all VNFs for an enterprise are deployed, a trigger initiates dynamic wiring.
   * Each VNF connects to the next (Firewall → LoadBalancer → WebServers), and internalOut/internalIn gates are used per enterprise.
5. **Client Traffic:** `Client` modules send requests to Firewall IPs.
6. **Traffic Flow:**

   * PacketSwitch forwards to NFVINode.
   * NFVINode uses `internalOut[gateIndex]` to send to Firewall.
   * VNFs forward through the chain.
   * WebServer generates response → flows back to client via `internalIn[gateIndex]` and `ethOut`.


## Future Enhancements

* **Dynamic Routing Table Updates:** `VnfManager` or `NFVO` configures PacketSwitch dynamically.
* **Multi-Chain Enterprise Support:** Support multiple service chains per enterprise.
* **Better Load Balancing:** Weighted or latency-aware algorithms.
* **Stateful VNF Logic:** Stateful firewalls, NATs, DPI, etc.
* **Advanced Monitoring and Logging:** Statistics on per-enterprise basis.
* **Fault Tolerance:** VNF/Node failure detection and recovery.
* **gRPC or External Orchestration:** Use real-time orchestrators via sockets or APIs.

---

This simulation provides a strong foundation for research or teaching on NFV, service chaining, and next-generation programmable networks.
