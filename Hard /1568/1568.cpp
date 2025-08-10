#include <vector>
#include <queue> // Optional, can use DFS or BFS. DFS is simpler here.

class Solution {
private:
    int M;
    int N;
    std::vector<std::vector<int>> current_grid; // To avoid passing by value/copying
    std::vector<std::vector<bool>> visited; // Visited array for DFS/BFS
    
    // Directions for 4-directional movement
    int dr[4] = {-1, 1, 0, 0}; // Row offsets: Up, Down, None, None
    int dc[4] = {0, 0, -1, 1}; // Col offsets: None, None, Left, Right

    // DFS to explore connected land cells and mark them as visited
    void dfs(int r, int c) {
        if (r < 0 || r >= M || c < 0 || c >= N || current_grid[r][c] == 0 || visited[r][c]) {
            return;
        }
        visited[r][c] = true;
        for (int i = 0; i < 4; ++i) {
            dfs(r + dr[i], c + dc[i]);
        }
    }

    // Function to count the number of islands in the grid
    int countIslands() {
        visited.assign(M, std::vector<bool>(N, false)); // Reset visited for each call
        int num_islands = 0;
        for (int r = 0; r < M; ++r) {
            for (int c = 0; c < N; ++c) {
                if (current_grid[r][c] == 1 && !visited[r][c]) {
                    num_islands++;
                    dfs(r, c);
                }
            }
        }
        return num_islands;
    }

public:
    int minDays(std::vector<std::vector<int>>& grid) {
        M = grid.size();
        N = grid[0].size();
        current_grid = grid; // Make a copy to modify

        // Case 0: Already disconnected (0 or >1 islands)
        if (countIslands() != 1) {
            return 0;
        }

        // Case 1: Disconnect in one day
        for (int r = 0; r < M; ++r) {
            for (int c = 0; c < N; ++c) {
                if (current_grid[r][c] == 1) {
                    current_grid[r][c] = 0; // Temporarily change land to water
                    if (countIslands() != 1) {
                        return 1; // Disconnected in one day
                    }
                    current_grid[r][c] = 1; // Revert change for next iteration
                }
            }
        }

        // Case 2: If not disconnected in 0 or 1 day, it takes 2 days.
        // As per problem constraints, a valid arrangement always exists.
        // It's mathematically proven that for any 2-vertex-connected graph
        // (which an island that isn't disconnected by 1 cell removal would be),
        // removing at most 2 vertices is sufficient to disconnect it or
        // reduce it to a trivial graph (0 or 1 node).
        return 2;
    }
};
