class Solution {
    public int maxStudents(char[][] seats) {
        int m = seats.length, n = seats[0].length;
        int[] valid = new int[m];
        for (int i = 0; i < m; i++) {
            int mask = 0;
            for (int j = 0; j < n; j++)
                if (seats[i][j] == '.') mask |= (1 << j);
            valid[i] = mask;
        }
        int[][] dp = new int[m + 1][1 << n];
        for (int[] row : dp) java.util.Arrays.fill(row, -1);
        return dfs(0, 0, valid, n, m, dp);
    }
    private int dfs(int row, int prev, int[] valid, int n, int m, int[][] dp) {
        if (row == m) return 0;
        if (dp[row][prev] != -1) return dp[row][prev];
        int res = 0;
        for (int cur = 0; cur < (1 << n); cur++) {
            if ((cur & valid[row]) == cur && (cur & (cur >> 1)) == 0 && (cur & (prev >> 1)) == 0 && (cur & (prev << 1)) == 0) {
                res = Math.max(res, Integer.bitCount(cur) + dfs(row + 1, cur, valid, n, m, dp));
            }
        }
        return dp[row][prev] = res;
    }
}
