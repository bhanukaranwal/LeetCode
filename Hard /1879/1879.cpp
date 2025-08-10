#include <vector>
#include <climits>
#include <cstring>

class Solution {
public:
    int minimumXORSum(std::vector<int>& nums1, std::vector<int>& nums2) {
        int n = nums1.size();
        std::vector<int> dp(1 << n, INT_MAX);
        dp[0] = 0;
        
        // Iterate through all possible subsets of nums2 (bitmask)
        for (int mask = 0; mask < (1 << n); ++mask) {
            // Count number of set bits (used elements from nums2)
            int used = __builtin_popcount(mask);
            if (used >= n) continue;
            
            // Try pairing current nums1 element with each unused nums2 element
            for (int j = 0; j < n; ++j) {
                if (!(mask & (1 << j))) { // If nums2[j] is not used
                    int new_mask = mask | (1 << j);
                    dp[new_mask] = std::min(dp[new_mask], 
                                          dp[mask] + (nums1[used] ^ nums2[j]));
                }
            }
        }
        
        return dp[(1 << n) - 1];
    }
};
