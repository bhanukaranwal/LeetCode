import java.util.*;

class Solution {
    public int shortestPath(int[][] grid, int k) {
        int m = grid.length, n = grid[0].length;
        if (m == 1 && n == 1) return 0;
        int[][][] visited = new int[m][n][k + 1];
        Queue<int[]> q = new LinkedList<>();
        q.offer(new int[]{0, 0, 0, k});
        visited[0][0][k] = 1;
        int[][] dirs = {{0,1},{1,0},{0,-1},{-1,0}};
        while (!q.isEmpty()) {
            int[] curr = q.poll();
            int x = curr[0], y = curr[1], steps = curr[2], rem = curr[3];
            for (int[] d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
                    int nrem = rem - grid[nx][ny];
                    if (nrem >= 0 && visited[nx][ny][nrem] == 0) {
                        if (nx == m - 1 && ny == n - 1) return steps + 1;
                        visited[nx][ny][nrem] = 1;
                        q.offer(new int[]{nx, ny, steps + 1, nrem});
                    }
                }
            }
        }
        return -1;
    }
}
