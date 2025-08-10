import java.util.Arrays;

class Solution {
    public int minDistance(int[] houses, int k) {
        Arrays.sort(houses);
        int n = houses.length;
        int[][] cost = new int[n][n];
        
        // Precompute cost[i][j]: min distance to serve houses[i..j] with 1 mailbox
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                int median = houses[(i + j) / 2];
                for (int x = i; x <= j; ++x)
                    cost[i][j] += Math.abs(houses[x] - median);
            }
        }
        
        // dp[i][k]: min cost to serve houses[i..n-1] with k mailboxes
        int[][] dp = new int[n + 1][k + 1];
        for (int[] row : dp) Arrays.fill(row, Integer.MAX_VALUE / 2);
        dp[n][0] = 0;
        
        for (int i = n - 1; i >= 0; --i) {
            for (int m = 1; m <= k; ++m) {
                for (int j = i; j < n; ++j) {
                    dp[i][m] = Math.min(dp[i][m], cost[i][j] + dp[j + 1][m - 1]);
                }
            }
        }
        return dp[0][k];
    }
}
