import java.util.*;

class Solution {
    public int largestIsland(int[][] grid) {
        int n = grid.length;
        int islandId = 2; // start from 2 to distinguish from 0 and 1
        Map<Integer, Integer> area = new HashMap<>();
        int max = 0;
        // Step 1: Label each island with a unique id and record its area
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    int a = dfs(grid, i, j, islandId);
                    area.put(islandId, a);
                    max = Math.max(max, a);
                    islandId++;
                }
            }
        }
        // Step 2: Try changing each 0 to 1 and calculate the connected area
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 0) {
                    Set<Integer> seen = new HashSet<>();
                    int sum = 1;
                    for (int[] d : DIRS) {
                        int ni = i + d[0], nj = j + d[1];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] > 1) {
                            int id = grid[ni][nj];
                            if (seen.add(id)) {
                                sum += area.get(id);
                            }
                        }
                    }
                    max = Math.max(max, sum);
                }
            }
        }
        // If all 1's, max is already the answer
        return max == 0 ? n * n : max;
    }

    private static final int[][] DIRS = {{1,0},{-1,0},{0,1},{0,-1}};

    private int dfs(int[][] grid, int i, int j, int id) {
        int n = grid.length;
        grid[i][j] = id;
        int res = 1;
        for (int[] d : DIRS) {
            int ni = i + d[0], nj = j + d[1];
            if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj] == 1) {
                res += dfs(grid, ni, nj, id);
            }
        }
        return res;
    }
}
