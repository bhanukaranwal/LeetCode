#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    int trapRainWater(vector<vector<int>>& heightMap) {
        int m = heightMap.size(), n = heightMap[0].size();
        if (m <= 2 || n <= 2) return 0; // No space to trap water

        using Cell = tuple<int, int, int>; // (height, row, col)
        priority_queue<Cell, vector<Cell>, greater<Cell>> minHeap;
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        // Push all boundary cells into the heap and mark as visited
        for (int i = 0; i < m; ++i) {
            minHeap.emplace(heightMap[i][0], i, 0);
            minHeap.emplace(heightMap[i][n-1], i, n-1);
            visited[i][0] = visited[i][n-1] = true;
        }
        for (int j = 1; j < n-1; ++j) {
            minHeap.emplace(heightMap[0][j], 0, j);
            minHeap.emplace(heightMap[m-1][j], m-1, j);
            visited[0][j] = visited[m-1][j] = true;
        }

        int trapped = 0;
        const int dirs[4][2] = {{-1,0},{1,0},{0,-1},{0,1}};
        while (!minHeap.empty()) {
            auto [h, x, y] = minHeap.top(); minHeap.pop();
            for (auto& d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny]) continue;
                trapped += max(0, h - heightMap[nx][ny]);
                minHeap.emplace(max(h, heightMap[nx][ny]), nx, ny);
                visited[nx][ny] = true;
            }
        }
        return trapped;
    }
};
