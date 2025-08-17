class Solution {
public:
    int m, n;
    vector<vector<vector<int>>> dp;

    bool dfs(const vector<vector<char>>& grid, int i, int j, int open) {
        // Out of bounds or more closing than opening
        if (i < 0 || i >= m || j < 0 || j >= n || open < 0) return false;
        // If more opens than total remaining cells, impossible to close them all
        if (open > (m - 1 - i) + (n - 1 - j) + 1) return false;
        // Memoization
        if (dp[i][j][open] != -1) return dp[i][j][open];

        int newOpen = open + (grid[i][j] == '(' ? 1 : -1);
        if (newOpen < 0) return dp[i][j][open] = false;

        // At the end, valid if all opened are closed
        if (i == m - 1 && j == n - 1) return dp[i][j][open] = (newOpen == 0);

        // Move right or down
        bool res = false;
        if (i + 1 < m) res |= dfs(grid, i + 1, j, newOpen);
        if (j + 1 < n) res |= dfs(grid, i, j + 1, newOpen);
        return dp[i][j][open] = res;
    }

    bool hasValidPath(vector<vector<char>>& grid) {
        m = grid.size();
        n = grid[0].size();
        // The max open at any point can't be more than m+n (path length)
        dp.assign(m, vector<vector<int>>(n, vector<int>(m + n + 1, -1)));
        return dfs(grid, 0, 0, 0);
    }
};
