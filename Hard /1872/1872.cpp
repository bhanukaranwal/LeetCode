#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
public:
    long long stoneGameVIII(std::vector<int>& stones) {
        int n = stones.size();
        
        // Step 1: Compute prefix sums for efficient score calculation.
        std::vector<long long> prefixSum(n);
        prefixSum[0] = stones[0];
        for (int i = 1; i < n; ++i) {
            prefixSum[i] = prefixSum[i - 1] + stones[i];
        }

        // Step 2: Apply the dynamic programming logic.
        // We can optimize space by noticing we only need the result from the next state.
        // `dp` here represents the optimal score difference from the end of the game.
        // Initialize with the base case: when only two stones are left (state n-2),
        // the player takes them for a score of prefixSum[n-1].
        long long dp = prefixSum[n - 1];
        
        // Iterate backwards from the second to last state.
        for (int i = n - 2; i > 0; --i) {
            // The current player chooses between taking more stones (first term)
            // or passing the turn (second term, which is the existing dp value).
            dp = std::max(dp, prefixSum[i] - dp);
        }

        return dp;
    }
};
