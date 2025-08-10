class Solution {
    public int cherryPickup(int[][] grid) {
        int rows = grid.length, cols = grid[0].length;
        int[][][] memo = new int[rows][cols][cols];
        for (int[][] layer : memo)
            for (int[] row : layer)
                java.util.Arrays.fill(row, -1);
        return dp(grid, 0, 0, cols - 1, memo);
    }

    // dp(x, y1, y2): max cherries from row x, robot1 at y1, robot2 at y2
    private int dp(int[][] grid, int x, int y1, int y2, int[][][] memo) {
        int rows = grid.length, cols = grid[0].length;
        if (y1 < 0 || y1 >= cols || y2 < 0 || y2 >= cols) return 0;
        if (x == rows) return 0;
        if (memo[x][y1][y2] != -1) return memo[x][y1][y2];
        int cherries = grid[x][y1];
        if (y1 != y2) cherries += grid[x][y2];
        int max = 0;
        for (int d1 = -1; d1 <= 1; d1++) {
            for (int d2 = -1; d2 <= 1; d2++) {
                max = Math.max(max, dp(grid, x + 1, y1 + d1, y2 + d2, memo));
            }
        }
        memo[x][y1][y2] = cherries + max;
        return memo[x][y1][y2];
    }
}
