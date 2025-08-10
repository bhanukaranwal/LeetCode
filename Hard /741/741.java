class Solution {
    int n;
    int[][][] memo;
    public int cherryPickup(int[][] grid) {
        n = grid.length;
        memo = new int[n][n][n];
        for (int[][] arr2 : memo)
            for (int[] arr1 : arr2)
                Arrays.fill(arr1, Integer.MIN_VALUE);
        int res = Math.max(0, dp(grid, 0, 0, 0));
        return res;
    }
    // x1,y1: first person, x2,y2: second person, but y2 = x1 + y1 - x2
    private int dp(int[][] grid, int x1, int y1, int x2) {
        int y2 = x1 + y1 - x2;
        if (x1 >= n || y1 >= n || x2 >= n || y2 >= n ||
            grid[x1][y1] == -1 || grid[x2][y2] == -1)
            return -99999;
        if (x1 == n-1 && y1 == n-1) return grid[x1][y1];
        if (memo[x1][y1][x2] != Integer.MIN_VALUE) return memo[x1][y1][x2];
        int cherries = grid[x1][y1];
        if (x1 != x2 || y1 != y2) cherries += grid[x2][y2];
        int best = Math.max(
            Math.max(dp(grid, x1+1, y1, x2+1), dp(grid, x1, y1+1, x2)),
            Math.max(dp(grid, x1+1, y1, x2), dp(grid, x1, y1+1, x2+1))
        );
        cherries += best;
        memo[x1][y1][x2] = cherries;
        return cherries;
    }
}
