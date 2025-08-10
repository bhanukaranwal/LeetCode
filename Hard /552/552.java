class Solution {
    public int checkRecord(int n) {
        int MOD = 1000000007;
        long[][][] dp = new long[n + 1][2][3];
        dp[0][0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int a = 0; a < 2; a++) {
                for (int l = 0; l < 3; l++) {
                    dp[i][a][0] = (dp[i][a][0] + dp[i - 1][a][l]) % MOD;
                    if (l < 2) dp[i][a][l + 1] = (dp[i][a][l + 1] + dp[i - 1][a][l]) % MOD;
                    if (a < 1) dp[i][a + 1][0] = (dp[i][a + 1][0] + dp[i - 1][a][l]) % MOD;
                }
            }
        }
        long res = 0;
        for (int a = 0; a < 2; a++)
            for (int l = 0; l < 3; l++)
                res = (res + dp[n][a][l]) % MOD;
        return (int)res;
    }
}
