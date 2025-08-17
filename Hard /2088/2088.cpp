#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int countPyramids(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        auto count = [&](vector<vector<int>>& g) {
            int res = 0;
            vector<vector<int>> dp = g;
            for (int i = 1; i < m; ++i) {
                for (int j = 1; j < n-1; ++j) {
                    if (g[i][j] && g[i-1][j-1] && g[i-1][j] && g[i-1][j+1]) {
                        dp[i][j] = min({dp[i-1][j-1], dp[i-1][j], dp[i-1][j+1]}) + 1;
                        res += dp[i][j] - 1;
                    }
                }
            }
            return res;
        };
        int total = count(grid);
        reverse(grid.begin(), grid.end());
        total += count(grid);
        return total;
    }
};
