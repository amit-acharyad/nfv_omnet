// Base message
packet ServiceMessage {}

// ServiceChainRequest extends ServiceMessage
packet ServiceChainRequest extends ServiceMessage {
    int enterpriseId;             // ID of tenant
    string chainType;             // E.g., "Firewall->LB->Server"
    int desiredServerCount;       // Number of servers requested
}

// ServiceChainAck extends ServiceMessage
packet ServiceChainAck extends ServiceMessage {
    int enterpriseId;
    int nfviNodeId;
    bool success;
    string messageinfo;               // Optional info or error message
}