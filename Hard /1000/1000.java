class Solution {
    private static final int INF = 1_000_000_000;

    public int mergeStones(int[] stones, int k) {
        int n = stones.length;
        if ((n - 1) % (k - 1) != 0) return -1; // Impossible case

        int[] prefix = new int[n + 1];
        for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + stones[i];

        int[][][] dp = new int[n][n][k + 1];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                for (int m = 0; m <= k; ++m)
                    dp[i][j][m] = INF;

        for (int i = 0; i < n; ++i) dp[i][i][1] = 0;

        for (int len = 2; len <= n; ++len) {
            for (int i = 0; i + len - 1 < n; ++i) {
                int j = i + len - 1;
                for (int m = 2; m <= k; ++m) {
                    for (int mid = i; mid < j; mid += k - 1) {
                        dp[i][j][m] = Math.min(dp[i][j][m],
                            dp[i][mid][1] + dp[mid + 1][j][m - 1]);
                    }
                }
                // Merge k piles into 1 pile
                if (dp[i][j][k] < INF)
                    dp[i][j][1] = dp[i][j][k] + prefix[j + 1] - prefix[i];
            }
        }
        return dp[0][n - 1][1];
    }
}
