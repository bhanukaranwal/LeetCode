import java.util.*;

class Solution {
    public int minCost(int[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[][] dirs = {{0,1},{0,-1},{1,0},{-1,0}};
        int[][] cost = new int[m][n];
        for (int[] row : cost) Arrays.fill(row, Integer.MAX_VALUE);
        Deque<int[]> dq = new ArrayDeque<>();
        dq.offerFirst(new int[]{0, 0, 0});
        while (!dq.isEmpty()) {
            int[] cur = dq.pollFirst();
            int x = cur[0], y = cur[1], c = cur[2];
            if (x < 0 || x >= m || y < 0 || y >= n || c >= cost[x][y]) continue;
            cost[x][y] = c;
            for (int d = 0; d < 4; d++) {
                int nx = x + dirs[d][0], ny = y + dirs[d][1];
                int nc = c + ((grid[x][y] == d + 1) ? 0 : 1);
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && nc < cost[nx][ny]) {
                    if (grid[x][y] == d + 1) dq.offerFirst(new int[]{nx, ny, nc});
                    else dq.offerLast(new int[]{nx, ny, nc});
                }
            }
        }
        return cost[m-1][n-1];
    }
}
