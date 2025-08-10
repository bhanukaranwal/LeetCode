#include <vector>
#include <algorithm> // For std::min

class Solution {
public:
    std::vector<std::vector<int>> adj;
    std::vector<int> disc; // Discovery time of each node
    std::vector<int> low;  // Low-link value of each node
    std::vector<std::vector<int>> critical_connections_found;
    int time_counter; // Global time counter for discovery times

    void dfs(int u, int p) { // u: current node, p: parent of u in DFS tree
        disc[u] = low[u] = time_counter++; // Set discovery and low-link time for u
        
        for (int v : adj[u]) {
            if (v == p) { // Don't go back to the immediate parent
                continue;
            }
            
            if (disc[v] == -1) { // If v is not visited
                dfs(v, u); // Recurse on v
                
                low[u] = std::min(low[u], low[v]); // Update u's low-link value based on v's subtree
                
                // If the lowest reachable node from v (and its subtree) is still deeper than u,
                // then (u, v) is a bridge.
                if (low[v] > disc[u]) {
                    critical_connections_found.push_back({u, v});
                }
            } else { // v is visited and not parent (it's a back-edge to an ancestor or already visited node)
                low[u] = std::min(low[u], disc[v]); // Update u's low-link value with v's discovery time
            }
        }
    }

    std::vector<std::vector<int>> criticalConnections(int n, std::vector<std::vector<int>>& connections) {
        adj.assign(n, std::vector<int>()); // Initialize adjacency list
        disc.assign(n, -1); // Initialize discovery times to -1 (unvisited)
        low.assign(n, -1);  // Initialize low-link values to -1
        critical_connections_found.clear(); // Clear results from previous runs (if any)
        time_counter = 0; // Reset time counter

        // Build the adjacency list from connections
        for (const auto& conn : connections) {
            adj[conn[0]].push_back(conn[1]);
            adj[conn[1]].push_back(conn[0]); // Undirected graph
        }

        // Start DFS from node 0. Since the problem guarantees connectivity,
        // a single DFS from any node will visit all nodes/edges.
        dfs(0, -1); // -1 indicates no parent for the starting node

        return critical_connections_found;
    }
};
