class Solution {
    public int minDifficulty(int[] jobDifficulty, int d) {
        int n = jobDifficulty.length;
        if (n < d) return -1;
        int[][] dp = new int[d + 1][n + 1];
        for (int i = 0; i <= d; i++)
            for (int j = 0; j <= n; j++)
                dp[i][j] = 1000000;
        dp[0][0] = 0;
        for (int day = 1; day <= d; day++) {
            for (int i = day; i <= n; i++) {
                int max = 0;
                for (int k = i - 1; k >= day - 1; k--) {
                    max = Math.max(max, jobDifficulty[k]);
                    dp[day][i] = Math.min(dp[day][i], dp[day - 1][k] + max);
                }
            }
        }
        return dp[d][n];
    }
}
