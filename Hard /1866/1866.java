class Solution {
    public int rearrangeSticks(int n, int k) {
        int MOD = 1_000_000_007;
        // dp[i][j] = #ways to arrange i sticks so that j are visible
        int[][] dp = new int[n+1][k+1];
        dp[0][0] = 1;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= k; ++j) {
                // Place tallest at left (visible) or not at left (not visible)
                dp[i][j] = (int)((dp[i-1][j-1] + (long)(i-1) * dp[i-1][j]) % MOD);
            }
        }
        return dp[n][k];
    }
}
