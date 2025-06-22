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

packet VnfDeploymentRequest extends NfvMessage {
string vnfType; //eg. firewall loadbalancer
double requiredCpu;
double requiredMemory;
double requiredBandwidth;
int requestId; // unique id for this deployment
}

packet VnfDeploymentResponse extends NfvMessage{
int requestId; // reference to original request
bool success;
string deploymentId; //unique id of deployed Vnf instance
string errorMessage; //reason for failure (if not successful)
int nfviNodeId; // Id of the nfvi node that responded

}
