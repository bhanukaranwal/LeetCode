#include <string>
#include <vector>
#include <set>
#include <map> // For std::map
#include <algorithm> // For std::reverse
#include <functional> // For std::function (for recursive lambda)

class Solution {
public:
    std::string crackSafe(int n, int k) {
        if (n == 1) {
            // For n=1, the password is a single digit.
            // The shortest string containing all 0 to k-1 digits is "012...(k-1)".
            std::string res = "";
            for (int i = 0; i < k; ++i) {
                res += (char)('0' + i);
            }
            return res;
        }

        // `circuit_nodes` will store the sequence of appended digits in reverse order
        std::vector<char> circuit_nodes;
        // `ptr` maps each (n-1)-length prefix (node) to the index of the next digit (0 to k-1) to try.
        std::map<std::string, int> ptr;

        // The starting node (prefix) for the Eulerian path. It's 'n-1' zeros.
        std::string start_node = std::string(n - 1, '0');

        // Hierholzer's algorithm using DFS
        // Lambda function for the recursive DFS
        std::function<void(std::string)> hierholzer_dfs =
            [&](std::string u) { // 'u' is the current (n-1)-length prefix (node)
            // Iterate through possible next digits from 0 to k-1
            // The `ptr[u]` acts as an iterator for the outgoing edges from node 'u'.
            while (ptr[u] < k) {
                int i = ptr[u];
                ptr[u]++; // Increment the pointer to mark this edge as considered/used for current traversal

                char digit = i + '0'; // Convert integer digit to character
                // The next (n-1)-length prefix (node) formed by appending 'digit'
                std::string v = u.substr(1) + digit;

                hierholzer_dfs(v); // Recursively call DFS on the next node

                // After the recursive call returns (meaning the sub-path from 'v' is fully explored),
                // add the current digit to the `circuit_nodes`.
                // This builds the Eulerian path in reverse order.
                circuit_nodes.push_back(digit);
            }
        };

        // Start the DFS from the initial node
        hierholzer_dfs(start_node);

        // The `circuit_nodes` now contains the k^n digits in reverse order.
        // Reverse it to get the correct sequence of appended digits.
        std::reverse(circuit_nodes.begin(), circuit_nodes.end());

        // The final password string starts with the initial (n-1) zeros,
        // followed by all the digits collected in `circuit_nodes`.
        // The total length will be (n-1) + k^n.
        std::string final_password = start_node;
        for (char c : circuit_nodes) {
            final_password += c;
        }

        return final_password;
    }
};
