import java.util.*;

class Solution {
    public int shortestPathAllKeys(String[] grid) {
        int m = grid.length, n = grid[0].length();
        int allKeys = 0, startX = 0, startY = 0;
        // Find start and count all keys
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                char c = grid[i].charAt(j);
                if (c == '@') {
                    startX = i; startY = j;
                } else if (c >= 'a' && c <= 'f') {
                    allKeys |= (1 << (c - 'a'));
                }
            }
        }
        Queue<int[]> queue = new ArrayDeque<>();
        boolean[][][] visited = new boolean[m][n][1 << 6];
        queue.offer(new int[]{startX, startY, 0});
        visited[startX][startY][0] = true;
        int steps = 0;
        int[][] dirs = {{0,1},{0,-1},{1,0},{-1,0}};
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int s = 0; s < size; ++s) {
                int[] curr = queue.poll();
                int x = curr[0], y = curr[1], keys = curr[2];
                if (keys == allKeys) return steps;
                for (int[] d : dirs) {
                    int nx = x + d[0], ny = y + d[1], nkeys = keys;
                    if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
                    char nc = grid[nx].charAt(ny);
                    if (nc == '#') continue;
                    if (nc >= 'a' && nc <= 'f') nkeys |= (1 << (nc - 'a'));
                    if (nc >= 'A' && nc <= 'F' && ((nkeys >> (nc - 'A')) & 1) == 0) continue;
                    if (!visited[nx][ny][nkeys]) {
                        visited[nx][ny][nkeys] = true;
                        queue.offer(new int[]{nx, ny, nkeys});
                    }
                }
            }
            steps++;
        }
        return -1;
    }
}
