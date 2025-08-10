#include <vector>
#include <algorithm> // For std::sort
#include <tuple>   // For std::tuple
#include <climits> // For INT_MAX, INT_MIN (though not directly used in the Trie logic itself)

// Define the maximum number of bits for the integers (up to 10^9 < 2^30)
// We need to consider bits from 29 down to 0 (total 30 bits)
const int MAX_BITS = 29; 

// Maximum possible nodes in the Trie:
// N (max numbers) * MAX_BITS (max depth) = 10^5 * 30 = 3 * 10^6 nodes.
// Add a small buffer for safety.
const int MAX_TRIE_NODES = 3000000 + 5; 

// Global arrays to represent the Trie.
// `trie[node_idx][0]` stores the index of the child for bit 0.
// `trie[node_idx][1]` stores the index of the child for bit 1.
// We use 0 to indicate a null/non-existent child. Node indices will start from 0.
int trie[MAX_TRIE_NODES][2]; 
int node_count; // Global counter for the next available node index.
                // It represents the total number of nodes currently in use.
                // Node 0 is implicitly the root.

// Function to initialize the Trie for a new set of operations (crucial for multiple test cases)
void init_trie() {
    node_count = 0; // Start with 0 nodes. The root will be node 0.
    // Initialize the root node's children to 0 (null)
    trie[0][0] = 0; 
    trie[0][1] = 0;
}

// Inserts a number into the Trie
void insert_num(int num) {
    int curr_node_idx = 0; // Start from the root node (index 0)
    for (int i = MAX_BITS; i >= 0; --i) {
        int bit = (num >> i) & 1; // Get the i-th bit of num
        if (trie[curr_node_idx][bit] == 0) { // If child doesn't exist (represented by 0)
            node_count++; // Allocate a new node (increment count to get next index)
            // Initialize the new node's children to 0
            trie[node_count][0] = 0; 
            trie[node_count][1] = 0;
            // Link current node to the newly created child
            trie[curr_node_idx][bit] = node_count; 
        }
        curr_node_idx = trie[curr_node_idx][bit]; // Move to the child node
    }
}

// Queries the Trie for the maximum XOR value with 'num'
// Assumes the Trie is not empty (i.e., at least one number has been inserted)
int query_max_xor_val(int num) {
    int curr_node_idx = 0; // Start from the root node (index 0)
    int current_xor_val = 0;
    for (int i = MAX_BITS; i >= 0; --i) {
        int bit = (num >> i) & 1; // Get the i-th bit of num
        int target_bit = 1 - bit; // Try to find the opposite bit to maximize XOR

        if (trie[curr_node_idx][target_bit] != 0) { // If the opposite bit path exists
            current_xor_val |= (1 << i); // Set the i-th bit in our XOR result
            curr_node_idx = trie[curr_node_idx][target_bit]; // Move to the child node
        } else {
            // Otherwise, we are forced to take the same bit path
            curr_node_idx = trie[curr_node_idx][bit]; // Move to the child node
        }
    }
    return current_xor_val;
}

class Solution {
public:
    std::vector<int> maximizeXor(std::vector<int>& nums, std::vector<std::vector<int>>& queries) {
        // Initialize the Trie for each function call to ensure a clean state
        // This is crucial in competitive programming where multiple test cases
        // might use the same global variables.
        init_trie(); 

        // Step 1: Sort nums in ascending order.
        // This allows us to add numbers to the Trie incrementally based on 'mi'.
        std::sort(nums.begin(), nums.end());

        // Step 2: Store queries along with their original indices and sort them by mi.
        // Tuple format: {mi, xi, original_index}
        std::vector<std::tuple<int, int, int>> sorted_queries;
        for (int i = 0; i < queries.size(); ++i) {
            sorted_queries.emplace_back(queries[i][1], queries[i][0], i);
        }
        std::sort(sorted_queries.begin(), sorted_queries.end());

        std::vector<int> ans(queries.size()); // To store results in original query order
        
        int nums_ptr = 0; // Pointer for iterating through sorted nums

        // Step 3: Process sorted queries
        for (const auto& q_tuple : sorted_queries) {
            int m = std::get<0>(q_tuple);
            int x = std::get<1>(q_tuple);
            int original_idx = std::get<2>(q_tuple);

            // Add all numbers from 'nums' that are <= 'm' to the Trie.
            // Since nums is sorted and queries are sorted by 'm', we only add
            // numbers that become relevant for the current 'm' and subsequent larger 'm's.
            while (nums_ptr < nums.size() && nums[nums_ptr] <= m) {
                insert_num(nums[nums_ptr]);
                nums_ptr++;
            }

            // Query the Trie for the maximum XOR value with 'x'.
            // The Trie only contains numbers less than or equal to the current 'm'.
            // If `node_count` is 0, it means no numbers have been inserted into the Trie yet
            // for the current `m` (or previous `m` values), implying no `nums[j] <= m` exists.
            if (node_count == 0) { 
                ans[original_idx] = -1;
            } else {
                ans[original_idx] = query_max_xor_val(x);
            }
        }

        return ans;
    }
};
