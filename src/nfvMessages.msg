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
packet NfvMessage{}
// Define VNF types using an enum for clarity
enum VnfType {
    VNF_TYPE_UNKNOWN = 0;
    VNF_TYPE_FIREWALL = 1;
    VNF_TYPE_LOADBALANCER = 2;
    VNF_TYPE_SERVER = 3; 
}

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
