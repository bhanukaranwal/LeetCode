class Solution {
    private static final int INF = 1000000000;
    private int[][][] memo;

    public int minCost(int[] houses, int[][] cost, int m, int n, int target) {
        memo = new int[m][n + 1][target + 1];
        for (int[][] layer : memo)
            for (int[] row : layer)
                java.util.Arrays.fill(row, -1);
        int res = dp(houses, cost, 0, 0, 0, m, n, target);
        return res == INF ? -1 : res;
    }

    // i: current house, prev: previous color, t: neighborhoods formed
    private int dp(int[] houses, int[][] cost, int i, int prev, int t, int m, int n, int target) {
        if (t > target) return INF;
        if (i == m) return t == target ? 0 : INF;
        if (memo[i][prev][t] != -1) return memo[i][prev][t];

        int res = INF;
        if (houses[i] != 0) {
            // Already painted, must use that color
            int newT = t + (houses[i] != prev ? 1 : 0);
            res = dp(houses, cost, i + 1, houses[i], newT, m, n, target);
        } else {
            // Try all colors
            for (int color = 1; color <= n; color++) {
                int newT = t + (color != prev ? 1 : 0);
                int currCost = cost[i][color - 1] + dp(houses, cost, i + 1, color, newT, m, n, target);
                res = Math.min(res, currCost);
            }
        }
        memo[i][prev][t] = res;
        return res;
    }
}
