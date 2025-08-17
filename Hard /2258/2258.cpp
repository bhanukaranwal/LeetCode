class Solution {
public:
    const int INF = 1e9 + 10;
    vector<vector<int>> dirs{{0,1},{1,0},{0,-1},{-1,0}};

    vector<vector<int>> fireTime(const vector<vector<int>>& grid, int m, int n) {
        vector<vector<int>> fire(m, vector<int>(n, INF));
        queue<pair<int,int>> q;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (grid[i][j] == 1) {
                    fire[i][j] = 0;
                    q.push({i, j});
                }
        while (!q.empty()) {
            auto [x, y] = q.front(); q.pop();
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 0 && fire[nx][ny] == INF) {
                    fire[nx][ny] = fire[x][y] + 1;
                    q.push({nx, ny});
                }
            }
        }
        return fire;
    }

    bool canEscape(const vector<vector<int>>& grid, const vector<vector<int>>& fire, int wait, int m, int n) {
        vector<vector<int>> vis(m, vector<int>(n, -1));
        queue<tuple<int,int,int>> q;
        if (wait >= fire[0][0]) return false;
        q.emplace(0, 0, wait);
        vis[0][0] = wait;
        while (!q.empty()) {
            auto [x, y, t] = q.front(); q.pop();
            if (x == m-1 && y == n-1) {
                if (t <= fire[x][y]) return true;
            }
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1], nt = t + 1;
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] == 0) {
                    if ((nx == m-1 && ny == n-1 && nt <= fire[nx][ny]) ||
                        (nx != m-1 || ny != n-1) && nt < fire[nx][ny]) {
                        if (vis[nx][ny] == -1 || nt < vis[nx][ny]) {
                            vis[nx][ny] = nt;
                            q.emplace(nx, ny, nt);
                        }
                    }
                }
            }
        }
        return false;
    }

    int maximumMinutes(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        auto fire = fireTime(grid, m, n);

        int lo = 0, hi = 1e9, ans = -1;
        while (lo <= hi) {
            int mid = lo + (hi - lo) / 2;
            if (canEscape(grid, fire, mid, m, n)) {
                ans = mid;
                lo = mid + 1;
            } else {
                hi = mid - 1;
            }
        }
        if (ans == -1) return -1;
        if (fire[m-1][n-1] >= 1e9) return 1000000000;
        return ans;
    }
};
