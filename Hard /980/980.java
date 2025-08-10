class Solution {
    private int res = 0, empty = 1, sx, sy, ex, ey;
    private int[][] dirs = {{0,1},{1,0},{0,-1},{-1,0}};

    public int uniquePathsIII(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        // Find start, end, and count empty squares (including start)
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) { sx = i; sy = j; }
                else if (grid[i][j] == 2) { ex = i; ey = j; }
                else if (grid[i][j] == 0) empty++;
            }
        }
        dfs(grid, sx, sy, 0);
        return res;
    }

    private void dfs(int[][] grid, int x, int y, int count) {
        if (x < 0 || y < 0 || x >= grid.length || y >= grid[0].length || grid[x][y] == -1) return;
        if (x == ex && y == ey) {
            if (count == empty) res++;
            return;
        }
        int temp = grid[x][y];
        grid[x][y] = -1; // Mark as visited
        for (int[] d : dirs) {
            int nx = x + d[0], ny = y + d[1];
            dfs(grid, nx, ny, count + 1);
        }
        grid[x][y] = temp; // Backtrack
    }
}
