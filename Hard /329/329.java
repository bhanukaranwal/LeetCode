class Solution {
    public int longestIncreasingPath(int[][] matrix) {
        int m = matrix.length, n = matrix[0].length, res = 0;
        int[][] memo = new int[m][n];
        int[] dirs = {0,1,0,-1,0};
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                res = Math.max(res, dfs(matrix, i, j, memo, dirs));
        return res;
    }
    private int dfs(int[][] matrix, int i, int j, int[][] memo, int[] dirs) {
        if (memo[i][j] != 0) return memo[i][j];
        int m = matrix.length, n = matrix[0].length, max = 1;
        for (int d = 0; d < 4; d++) {
            int x = i + dirs[d], y = j + dirs[d+1];
            if (x >= 0 && x < m && y >= 0 && y < n && matrix[x][y] > matrix[i][j])
                max = Math.max(max, 1 + dfs(matrix, x, y, memo, dirs));
        }
        memo[i][j] = max;
        return max;
    }
}
