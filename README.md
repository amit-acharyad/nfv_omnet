# 🧪 Basic NFV Implementation in OMNeT++

This project demonstrates a simple **Network Function Virtualization (NFV)** scenario using OMNeT++. It includes a basic service chain of:

- Multiple **Clients** sending packets  
- A central **Load Balancer VNF**  
- A **Firewall VNF**  
- Multiple **Servers** responding to client messages  

---

## 🔧 Components

- **Client**: Generates and sends messages to the network.
- **LoadBalancerVNF**: Distributes incoming client messages to available servers based on basic load-balancing logic (e.g., round-robin).
- **FirewallVNF**: Forwards packets and filters traffic (can be extended with rules).
- **Server**: Replies to messages received from clients.

---

## 🔁 Communication Flow

1. `Client[i]` sends a message to `LoadBalancerVNF`.
2. `LoadBalancerVNF` forwards it to `FirewallVNF`.
3. `FirewallVNF` sends it to the assigned `Server[j]`.
4. `Server[j]` sends a response back through the same path.
5. `FirewallVNF` forwards it back to `LoadBalancerVNF`.
6. `LoadBalancerVNF` routes the reply to the correct `Client[i]`.

---



