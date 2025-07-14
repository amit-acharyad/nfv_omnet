import vnftype;
packet NfvMessage{}
// Define VNF types using an enum for clarity


packet VnfDeploymentRequest extends NfvMessage {
	string vnfName; // Name for the VNF instance (e.g., "myFirewall1")
    VnfType vnfType; // New: The type of VNF to deploy (e.g., VNF_TYPE_FIREWALL)
	int requestId;
    // Resource requests (existing fields)
    double cpuRequest;
    double memoryRequest;
    double bandwidthRequest;

    // New: IP address assigned to this VNF instance
    int vnfIpAddress;

    // New: VNF-specific parameters (used conditionally based on vnfType)
    // For Firewall: the IP of the Load Balancer it should forward to
    int firewallLbVip = 0; // Initialize to 0, only relevant for Firewall

    // For LoadBalancer: the array of backend WebServerVNF IPs it manages
    int backendServerIps[]; // This will be set for LoadBalancer deployments
}

packet VnfDeploymentResponse extends NfvMessage{
int requestId; // reference to original request
bool success;
string vnfName;
string infoMessage;
int deployedVnfIp;

}
