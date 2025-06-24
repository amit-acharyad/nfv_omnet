# NFV Service Chain Simulation with OMNeT++

## Project Overview

This project implements a Network Functions Virtualization (NFV) service chain simulation using OMNeT++. It demonstrates the dynamic deployment of Virtual Network Functions (VNFs) on Network Function Virtualization Infrastructure (NFVI) nodes and the subsequent routing of client traffic through a defined service chain, including a Firewall, a Load Balancer, and multiple Web Servers.

The simulation aims to model the interaction between the Management and Orchestration (MANO) plane (NFVO, VNFManager) and the Data Plane (Clients, PacketSwitch, NFVINodes, VNFs).

## Key Features

* **Dynamic NFVI Node Deployment:** Easily configure the number of NFVI nodes in the network.
* **VNF Deployment & Lifecycle:**
    * `VnfManager` sends deployment requests to `NFVINode`s.
    * `NFVINode`s dynamically instantiate VNFs (Firewall, LoadBalancer, WebServerVNF) as submodules.
* **Simplified IP-based Routing:**
    * Packets are enhanced with `sourceAddress` and `destinationAddress` (simplified integer IPs).
    * `PacketSwitch` routes packets based on destination IP using a configurable routing table.
* **Network Service Chaining (Firewall, LoadBalancer, WebServerVNF):**
    * **Firewall VNF:** Receives traffic, (conceptually) applies filtering rules, and forwards it to the Load Balancer's VIP.
    * **LoadBalancer VNF:** Distributes incoming requests across multiple backend `WebServerVNF` instances using a round-robin algorithm.
    * **WebServerVNF:** Receives requests and generates corresponding responses, sending them back to the client.
* **Internal NFVINode Routing:** `NFVINode`s intelligently route packets between their external interface and hosted VNFs, and between chained VNFs located on the same node.
* **Request-Response Flow:** Simulates a complete communication cycle from client request to server response.

## Modules

The simulation is built using the following custom OMNeT++ modules:

* **`Client`**: Generates and sends data packets (requests) to the network.
* **`PacketSwitch`**: Acts as a central network switch, forwarding packets based on destination IP.
* **`NFVINode`**: Represents a physical server capable of hosting VNFs. It manages resource allocation and routes traffic to/from its hosted VNFs.
* **`VnfManager`**: Part of the MANO plane, responsible for sending VNF deployment requests to `NFVINode`s. (Future: Configures PacketSwitch routing).
* **`NFVO` (Network Function Virtualization Orchestrator)**: The top-level orchestrator. (Future: Defines service chains, selects NFVINodes for VNF placement, and orchestrates the overall network service).
* **`Firewall` (VNF)**: A virtual network function that filters and forwards traffic as the entry point of the service chain.
* **`LoadBalancer` (VNF)**: A virtual network function that distributes incoming requests across multiple backend servers.
* **`WebServerVNF` (VNF)**: A virtual network function simulating a web server that processes requests and generates responses.

## Prerequisites

* **OMNeT++ 6.0 or higher:** This project is built and tested with OMNeT++ 6.x.
* A C++ compiler (usually part of the OMNeT++ installation).

## Setup and Installation

1.  **Clone the repository:** (If this project is in a Git repo)
    ```bash
    git clone <repository_url>
    cd <project_directory>
    ```
2.  **Open in OMNeT++ IDE:**
    * Launch OMNeT++ IDE.
    * Go to `File -> Open Projects from File System...`.
    * Browse to the root directory of this project and click `Finish`.
3.  **Build the project:**
    * In the OMNeT++ IDE, right-click on the project in the Project Explorer.
    * Select `Build Project`. This will compile all C++ code and generate necessary files from `.ned` and `.msg` files.

## Usage

1.  **Configure Simulation:**
    * Open `omnetpp.ini`. You can adjust parameters like `numClients`, `numNfviNodes`, and specific VNF IPs here.
    * Example:
        ```ini
        [General]
        network = Nfvservicechain
        # ... other configurations ...

        # Number of clients and NFVI nodes
        Nfvservicechain.numClients = 4
        Nfvservicechain.numNfviNodes = 2

        # Configure VNF deployment details via VnfManager (future: NFVO sets this)
        # For initial testing, you might need to hardcode some VNF parameters in initialize()
        # or configure them via omnetpp.ini if your VnfManager can read them.
        ```
2.  **Run the Simulation:**
    * In the OMNeT++ IDE, right-click on `Nfvservicechain.ned` (or the project root).
    * Select `Run As -> OMNeT++ Simulation`.
    * The graphical simulation environment will appear. Click the "Run" button to start the simulation.
    * Observe the console output (for `EV` messages) and the animated packet flow in the GUI.

## Simulation Scenario

A typical simulation run involves:

1.  **Initialization:** `NFVO` and `VnfManager` initialize. `NFVINode`s come online.
2.  **VNF Deployment (Control Plane):** The `VnfManager` (or `NFVO` in future enhancements) initiates requests to deploy `Firewall`, `LoadBalancer`, and multiple `WebServerVNF` instances on the chosen `NFVINode`(s).
3.  **Data Plane Configuration (Future):** Once VNFs are deployed, the `VnfManager` will instruct the `PacketSwitch` to update its routing table to direct client traffic to the service's entry point (the Firewall's external IP).
4.  **Client Traffic (Data Plane):** `Client` modules start generating data packets with a `destinationAddress` set to the Firewall's IP.
5.  **Packet Forwarding:**
    * `PacketSwitch` forwards client packets to the correct `NFVINode`.
    * `NFVINode` internally routes packets from its external interface to the `Firewall`.
    * `Firewall` processes the packet, changes its destination to the `LoadBalancer`'s VIP.
    * `NFVINode` routes from `Firewall` to `LoadBalancer`.
    * `LoadBalancer` performs round-robin to select a `WebServerVNF`, changes the packet's destination to the chosen server's IP.
    * `NFVINode` routes from `LoadBalancer` to the `WebServerVNF`.
    * `WebServerVNF` processes the request, generates a response with the client's IP as destination, and sends it back.
    * The response packet traverses back through the `NFVINode` and `PacketSwitch` to the original `Client`.

## Future Enhancements (Ideas for further development)

* **Dynamic Routing Table Updates:** Implement the `VnfManager` explicitly sending routing configuration messages to the `PacketSwitch` to dynamically update its forwarding table upon VNF deployment.
* **NFVO Service Definition:** Enhance `NFVO` to define complex service chains programmatically and derive VNF deployment requests and IP assignments automatically.
* **VNF Scaling:** Implement logic for `NFVO`/`VnfManager` to dynamically scale up/down `WebServerVNF` instances based on load.
* **Resource Management:** More sophisticated resource tracking and allocation in `NFVINode`s (e.g., admitting/rejecting VNF deployments based on available capacity).
* **Failure Simulation:** Introduce VNF or NFVINode failures and implement recovery mechanisms.
* **Traffic Generation:** More realistic client traffic patterns and application-level messages.
* **Performance Metrics:** Detailed statistics collection (latency, throughput, packet loss) across the service chain.
* **Advanced VNF Logic:** More complex firewall rules, different load balancing algorithms, HTTP/application layer processing.
