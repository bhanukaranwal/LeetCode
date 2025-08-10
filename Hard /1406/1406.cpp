#include <vector>
#include <string>
#include <algorithm>

class Solution {
public:
    std::string stoneGameIII(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        // dp[i] stores the maximum score difference the current player can get
        // from the subarray starting at index i.
        std::vector<int> dp(n + 1, 0);

        // We iterate backwards from the end of the array.
        for (int i = n - 1; i >= 0; --i) {
            dp[i] = -1e9; // Initialize with a very small number.
            
            int current_sum = 0;
            // The current player considers taking 1, 2, or 3 stones.
            for (int j = 0; j < 3 && i + j < n; ++j) {
                current_sum += stoneValue[i + j];
                // The score for this move is what I take (current_sum) minus
                // the best my opponent can do on the rest (dp[i + j + 1]).
                int score = current_sum - dp[i + j + 1];
                dp[i] = std::max(dp[i], score);
            }
        }
        
        // dp[0] holds the final score difference for Alice (score1 - score2).
        if (dp[0] > 0) {
            return "Alice";
        }
        if (dp[0] < 0) {
            return "Bob";
        }
        return "Tie";
    }
};
