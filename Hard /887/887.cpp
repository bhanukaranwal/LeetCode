class Solution {
public:
    int superEggDrop(int k, int n) {
        // dp[m][k]: max floors that can be checked with k eggs and m moves
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        int m = 0;
        while (dp[m][k] < n) {
            ++m;
            for (int eggs = 1; eggs <= k; ++eggs) {
                dp[m][eggs] = dp[m-1][eggs-1] + dp[m-1][eggs] + 1;
            }
        }
        return m;
    }
};
