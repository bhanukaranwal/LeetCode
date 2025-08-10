class Solution {
    public int minSkips(int[] dist, int speed, int hoursBefore) {
        int n = dist.length;
        double INF = 1e15;
        // dp[i][j] = minimum time to reach end of i-th road with j skips
        double[][] dp = new double[n + 1][n + 1];
        for (int i = 0; i <= n; i++) {
            Arrays.fill(dp[i], INF);
        }
        dp[0][0] = 0.0;
        double eps = 1e-9;

        for (int i = 1; i <= n; i++) {
            double time = (double) dist[i - 1] / speed;
            for (int j = 0; j <= i; j++) {
                // Option 1: don't skip rest after i-1-th road (except last road)
                if (j < i) {
                    // ceil to next integer hour after traveling i-th road (except last)
                    dp[i][j] = Math.min(dp[i][j], Math.ceil(dp[i - 1][j] + time - eps));
                }
                // Option 2: skip rest after i-1-th road
                if (j > 0) {
                    dp[i][j] = Math.min(dp[i][j], dp[i - 1][j - 1] + time);
                }
            }
        }

        for (int j = 0; j <= n; j++) {
            if (dp[n][j] <= hoursBefore + eps) {
                return j;
            }
        }
        return -1;
    }
}
