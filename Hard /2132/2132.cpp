class Solution {
public:
    bool possibleToStamp(vector<vector<int>>& grid, int stampHeight, int stampWidth) {
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> sum(m + 1, vector<int>(n + 1));
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                sum[i][j] = grid[i-1][j-1] + sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
        vector<vector<int>> diff(m + 2, vector<int>(n + 2));
        for (int i = stampHeight; i <= m; ++i) {
            for (int j = stampWidth; j <= n; ++j) {
                int x1 = i - stampHeight + 1, y1 = j - stampWidth + 1;
                int x2 = i, y2 = j;
                int occupied = sum[x2][y2] - sum[x1-1][y2] - sum[x2][y1-1] + sum[x1-1][y1-1];
                if (occupied == 0) {
                    diff[x1][y1]++;
                    diff[x1][y2+1]--;
                    diff[x2+1][y1]--;
                    diff[x2+1][y2+1]++;
                }
            }
        }
        vector<vector<int>> cover(m + 2, vector<int>(n + 2));
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                cover[i][j] = diff[i][j] + cover[i-1][j] + cover[i][j-1] - cover[i-1][j-1];
        for (int i = 1; i <= m; ++i)
            for (int j = 1; j <= n; ++j)
                if (grid[i-1][j-1] == 0 && cover[i][j] == 0)
                    return false;
        return true;
    }
};
