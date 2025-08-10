class Solution {
    static final int MOD = 1_000_000_007;
    int[][] preSum;
    int[][][] memo;

    public int ways(String[] pizza, int k) {
        int rows = pizza.length, cols = pizza[0].length();
        preSum = new int[rows + 1][cols + 1];
        memo = new int[rows][cols][k + 1];

        // Build prefix sum: preSum[i][j] = apples in pizza[i:][j:]
        for (int i = rows - 1; i >= 0; i--) {
            for (int j = cols - 1; j >= 0; j--) {
                preSum[i][j] = (pizza[i].charAt(j) == 'A' ? 1 : 0)
                    + preSum[i + 1][j] + preSum[i][j + 1] - preSum[i + 1][j + 1];
            }
        }
        return dp(0, 0, k, rows, cols);
    }

    // dp(r, c, cuts_left): ways to cut pizza[r:][c:] into cuts_left pieces
    private int dp(int r, int c, int cuts, int rows, int cols) {
        if (preSum[r][c] == 0) return 0; // No apples in this subpizza
        if (cuts == 1) return 1; // Last piece and has at least one apple

        if (memo[r][c][cuts] != 0) return memo[r][c][cuts];

        int res = 0;
        // Try horizontal cuts
        for (int nr = r + 1; nr < rows; nr++) {
            if (preSum[r][c] - preSum[nr][c] > 0) // Top part has apple
                res = (res + dp(nr, c, cuts - 1, rows, cols)) % MOD;
        }
        // Try vertical cuts
        for (int nc = c + 1; nc < cols; nc++) {
            if (preSum[r][c] - preSum[r][nc] > 0) // Left part has apple
                res = (res + dp(r, nc, cuts - 1, rows, cols)) % MOD;
        }
        memo[r][c][cuts] = res;
        return res;
    }
}
