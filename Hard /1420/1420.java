class Solution {
    public int numOfArrays(int n, int m, int k) {
        int MOD = 1000000007;
        // dp[i][j][c]: #ways to fill i numbers, max value is j, search cost is c
        int[][][] dp = new int[n + 1][m + 1][k + 1];
        // base case: for length 1, cost 1, max j
        for (int j = 1; j <= m; j++) dp[1][j][1] = 1;
        for (int i = 2; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                for (int c = 1; c <= k; c++) {
                    // case 1: last element is <= current max (j)
                    dp[i][j][c] = (int)((dp[i][j][c] + (long)dp[i-1][j][c] * j) % MOD);
                    // case 2: last element is new max (j)
                    for (int prev = 1; prev < j; prev++) {
                        dp[i][j][c] = (dp[i][j][c] + dp[i-1][prev][c-1]) % MOD;
                    }
                }
            }
        }
        int ans = 0;
        for (int j = 1; j <= m; j++) ans = (ans + dp[n][j][k]) % MOD;
        return ans;
    }
}
