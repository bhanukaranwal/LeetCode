#include <vector>
#include <unordered_map> // Changed from map to unordered_map
#include <algorithm>     // For std::reverse
#include <functional>    // For std::function

class Solution {
public:
    std::vector<std::vector<int>> validArrangement(std::vector<std::vector<int>>& pairs) {
        // Adjacency list: maps source node to a list of destination nodes.
        // Using unordered_map for average O(1) access.
        std::unordered_map<int, std::vector<int>> adj;
        
        // Maps to store in-degree and out-degree for each node.
        std::unordered_map<int, int> in_degree;
        std::unordered_map<int, int> out_degree;
        
        // Populate adjacency list and calculate degrees
        for (const auto& pair : pairs) {
            int u = pair[0];
            int v = pair[1];
            adj[u].push_back(v); // This creates the entry if 'u' doesn't exist
            out_degree[u]++;
            in_degree[v]++;
        }

        int start_node = -1;

        // Find the starting node for the Eulerian path.
        // Iterate through all nodes that have outgoing edges.
        for (auto const& [node, out_deg] : out_degree) {
            // If a node's out-degree is one greater than its in-degree, it's the start node of an Eulerian path.
            if (out_deg == in_degree[node] + 1) {
                start_node = node;
                break; 
            }
        }

        // If no such node is found, it means all nodes have in-degree == out-degree,
        // implying an Eulerian circuit. In this case, we can start from any node that has outgoing edges.
        // The problem guarantees a valid arrangement exists, so `adj` won't be empty.
        if (start_node == -1) {
            start_node = adj.begin()->first;
        }

        // `path` will store the arrangement of pairs in reverse order.
        std::vector<std::vector<int>> path;
        
        // `adj_ptr` keeps track of the next available edge for each node.
        // It points to the index in the `adj[u]` vector.
        // Using unordered_map for average O(1) access.
        std::unordered_map<int, int> adj_ptr;

        // Hierholzer's DFS function
        // `u` is the current node
        std::function<void(int)> dfs = 
            [&](int u) {
            // While there are still unused edges from node `u`
            // `adj[u].size()` gives the total number of edges from `u`.
            // `adj_ptr[u]` gives the index of the next edge to consider.
            while (adj_ptr[u] < adj[u].size()) {
                int v = adj[u][adj_ptr[u]]; // Get the next destination
                adj_ptr[u]++;              // Increment pointer to mark this edge as used for current traversal
                
                dfs(v); // Recurse on the destination node

                // After the recursive call returns (meaning the sub-path from 'v' is fully explored),
                // add the current edge [u, v] to the path.
                // This builds the path in reverse order (post-order traversal).
                path.push_back({u, v});
            }
        };

        // Start DFS from the determined start node
        dfs(start_node);

        // The `path` vector currently holds pairs in reverse order.
        // Reverse it to get the correct chronological order.
        std::reverse(path.begin(), path.end());

        return path;
    }
};
