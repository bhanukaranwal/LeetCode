class Solution {
public:
    int maxValueOfCoins(vector<vector<int>>& piles, int k) {
        int n = piles.size();
        vector<int> dp(k + 1);
        for (auto& pile : piles) {
            vector<int> pre = dp;
            int sum = 0;
            for (int i = 0; i < pile.size() && i < k; ++i) {
                sum += pile[i];
                for (int j = k; j > i + 0; --j) {
                    dp[j] = max(dp[j], pre[j - i - 1] + sum);
                }
            }
        }
        return dp[k];
    }
};
