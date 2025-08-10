class Solution {
public:
    int maxProfit(int k, std::vector<int>& prices) {
        int n = prices.size();

        if (n == 0 || k == 0) {
            return 0;
        }

        // If k is large enough, it's equivalent to Best Time to Buy and Sell Stock II
        // (unlimited transactions)
        if (k >= n / 2) {
            int maxProf = 0;
            for (int i = 1; i < n; i++) {
                if (prices[i] > prices[i-1]) {
                    maxProf += prices[i] - prices[i-1];
                }
            }
            return maxProf;
        }

        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n, 0));

        for (int t = 1; t <= k; t++) {
            int max_diff = -prices[0]; // Represents max(dp[t-1][j] - prices[j])
            for (int i = 1; i < n; i++) {
                dp[t][i] = std::max(dp[t][i-1], prices[i] + max_diff);
                max_diff = std::max(max_diff, dp[t-1][i] - prices[i]);
            }
        }

        return dp[k][n-1];
    }
};
