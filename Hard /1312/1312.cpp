class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        // dp[i][j]: min insertions to make s[i..j] a palindrome
        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i+1][j-1];
                } else {
                    dp[i][j] = min(dp[i+1][j], dp[i][j-1]) + 1;
                }
            }
        }
        return dp[0][n-1];
    }
};
