class Solution {
    public int numWays(int steps, int arrLen) {
        int MOD = 1_000_000_007;
        int maxPos = Math.min(arrLen - 1, steps); // Can't go further than steps
        int[][] dp = new int[steps + 1][maxPos + 1];
        dp[0][0] = 1; // Start at index 0 with 0 steps

        for (int s = 1; s <= steps; s++) {
            for (int pos = 0; pos <= maxPos; pos++) {
                // Stay
                dp[s][pos] = dp[s - 1][pos];
                // Left
                if (pos > 0) dp[s][pos] = (dp[s][pos] + dp[s - 1][pos - 1]) % MOD;
                // Right
                if (pos < maxPos) dp[s][pos] = (dp[s][pos] + dp[s - 1][pos + 1]) % MOD;
            }
        }
        return dp[steps][0];
    }
}
