class Solution {
public:
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> arr(n + 2, 1);
        for (int i = 0; i < n; ++i) arr[i + 1] = nums[i];

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        // length is the distance between l and r
        for (int len = 2; len <= n + 1; ++len) {
            for (int l = 0; l + len <= n + 1; ++l) {
                int r = l + len;
                for (int i = l + 1; i < r; ++i) {
                    dp[l][r] = max(dp[l][r],
                        dp[l][i] + arr[l] * arr[i] * arr[r] + dp[i][r]);
                }
            }
        }
        return dp[0][n + 1];
    }
};
