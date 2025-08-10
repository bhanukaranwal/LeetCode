class Solution {
    static final int MOD = 1_000_000_007;

    public int profitableSchemes(int n, int minProfit, int[] group, int[] profit) {
        int m = group.length;
        // dp[people][profit] = number of schemes using up to 'people' and at least 'profit'
        int[][] dp = new int[n + 1][minProfit + 1];
        dp[0][0] = 1;
        for (int k = 0; k < m; ++k) {
            int g = group[k], p = profit[k];
            // Traverse people and profit in reverse to avoid overcounting
            for (int i = n; i >= g; --i) {
                for (int j = minProfit; j >= 0; --j) {
                    int newProfit = Math.min(minProfit, j + p);
                    dp[i][newProfit] = (dp[i][newProfit] + dp[i - g][j]) % MOD;
                }
            }
        }
        int res = 0;
        for (int i = 0; i <= n; ++i) {
            res = (res + dp[i][minProfit]) % MOD;
        }
        return res;
    }
}
