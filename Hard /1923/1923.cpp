#include <vector>
#include <string> // Not strictly needed for this problem, but often included
#include <unordered_set>
#include <algorithm> // For std::min

class Solution {
public:
    // Function to check if a common subpath of given length 'len' exists in all paths
    bool check(long long len, int n_cities, const std::vector<std::vector<int>>& paths) {
        if (len == 0) return true;

        // Use two different large prime moduli and bases to minimize hash collisions
        // Bases should be larger than the maximum possible city ID + 1 to reduce collisions effectively.
        // Max city ID is n-1, so max value is 10^5 - 1. Bases > 10^5 are good.
        long long M1 = 1e9 + 7;
        long long B1 = 100003; // A large prime base, > max city ID
        long long M2 = 1e9 + 9;
        long long B2 = 100007; // Another large prime base

        std::vector<long long> powB1(len + 1);
        std::vector<long long> powB2(len + 1);
        powB1[0] = 1;
        powB2[0] = 1;
        for (int i = 1; i <= len; ++i) {
            powB1[i] = (powB1[i - 1] * B1) % M1;
            powB2[i] = (powB2[i - 1] * B2) % M2;
        }

        // Use a single unordered_set to store combined hashes (hash1 * big_multiplier + hash2)
        std::unordered_set<long long> common_combined_hashes;

        // Process the first path to initialize common_combined_hashes
        if (paths[0].size() < len) {
            return false; // First path is too short
        }
        long long current_hash1 = 0;
        long long current_hash2 = 0;
        for (int i = 0; i < len; ++i) {
            // Add 1 to city ID to ensure all values are positive and non-zero
            // (especially important if using 0 for padding or initial hash states)
            current_hash1 = (current_hash1 * B1 + (paths[0][i] + 1)) % M1;
            current_hash2 = (current_hash2 * B2 + (paths[0][i] + 1)) % M2;
        }
        // Combine two hashes into a single long long for the unordered_set key
        // A common way is (hash1 << 32) | hash2, but this assumes hashes fit into 32 bits.
        // A safer way is hash1 * a_large_prime + hash2, ensuring uniqueness
        common_combined_hashes.insert(current_hash1 * M2 + current_hash2); // M2 is a prime, using it as multiplier

        for (int i = len; i < paths[0].size(); ++i) {
            current_hash1 = (current_hash1 - (paths[0][i - len] + 1) * powB1[len - 1] % M1 + M1) % M1;
            current_hash1 = (current_hash1 * B1 + (paths[0][i] + 1)) % M1;
            
            current_hash2 = (current_hash2 - (paths[0][i - len] + 1) * powB2[len - 1] % M2 + M2) % M2;
            current_hash2 = (current_hash2 * B2 + (paths[0][i] + 1)) % M2;

            common_combined_hashes.insert(current_hash1 * M2 + current_hash2);
        }

        // For subsequent paths, find hashes that are present in the current common_combined_hashes
        for (int p_idx = 1; p_idx < paths.size(); ++p_idx) {
            const auto& path = paths[p_idx];
            if (path.size() < len) {
                return false; // Current path is too short
            }

            std::unordered_set<long long> next_common_combined_hashes;

            current_hash1 = 0;
            current_hash2 = 0;
            for (int i = 0; i < len; ++i) {
                current_hash1 = (current_hash1 * B1 + (path[i] + 1)) % M1;
                current_hash2 = (current_hash2 * B2 + (path[i] + 1)) % M2;
            }

            if (common_combined_hashes.count(current_hash1 * M2 + current_hash2)) {
                next_common_combined_hashes.insert(current_hash1 * M2 + current_hash2);
            }

            for (int i = len; i < path.size(); ++i) {
                current_hash1 = (current_hash1 - (path[i - len] + 1) * powB1[len - 1] % M1 + M1) % M1;
                current_hash1 = (current_hash1 * B1 + (path[i] + 1)) % M1;
                
                current_hash2 = (current_hash2 - (path[i - len] + 1) * powB2[len - 1] % M2 + M2) % M2;
                current_hash2 = (current_hash2 * B2 + (path[i] + 1)) % M2;

                if (common_combined_hashes.count(current_hash1 * M2 + current_hash2)) {
                    next_common_combined_hashes.insert(current_hash1 * M2 + current_hash2);
                }
            }
            common_combined_hashes = next_common_combined_hashes;
            if (common_combined_hashes.empty()) { // No common hashes found in this path, so no common subpath of length 'len'
                return false;
            }
        }
        return !common_combined_hashes.empty(); // If we reach here, and common_hashes is not empty, a subpath exists
    }

    int longestCommonSubpath(int n, std::vector<std::vector<int>>& paths) {
        // Find the minimum path length to set the upper bound for binary search
        int min_path_len = 1e9 + 7; 
        for (const auto& path : paths) {
            min_path_len = std::min(min_path_len, (int)path.size());
        }

        int low = 0;
        int high = min_path_len;
        int ans = 0;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid, n, paths)) {
                ans = mid;
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return ans;
    }
};
