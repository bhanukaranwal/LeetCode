import java.util.*;

class Solution {
    public int minPushBox(char[][] grid) {
        int m = grid.length, n = grid[0].length;
        int[] box = new int[2], target = new int[2], player = new int[2];
        // Find initial positions
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 'B') { box[0] = i; box[1] = j; }
                if (grid[i][j] == 'T') { target[0] = i; target[1] = j; }
                if (grid[i][j] == 'S') { player[0] = i; player[1] = j; }
            }

        // State: [boxRow, boxCol, playerRow, playerCol, pushes]
        Queue<int[]> queue = new ArrayDeque<>();
        Set<String> visited = new HashSet<>();
        queue.offer(new int[]{box[0], box[1], player[0], player[1], 0});
        visited.add(box[0] + "," + box[1] + "," + player[0] + "," + player[1]);

        int[][] dirs = {{0,1},{0,-1},{1,0},{-1,0}};

        while (!queue.isEmpty()) {
            int[] state = queue.poll();
            int bx = state[0], by = state[1], px = state[2], py = state[3], pushes = state[4];
            if (bx == target[0] && by == target[1]) return pushes;

            // Try all four directions to push the box
            for (int d = 0; d < 4; d++) {
                int nbx = bx + dirs[d][0], nby = by + dirs[d][1]; // new box position
                int opx = bx - dirs[d][0], opy = by - dirs[d][1]; // player's position to push

                if (!inBounds(nbx, nby, m, n) || grid[nbx][nby] == '#') continue;
                if (!inBounds(opx, opy, m, n) || grid[opx][opy] == '#') continue;

                // Can the player reach opx, opy without crossing the box?
                if (!canReach(grid, px, py, opx, opy, bx, by)) continue;

                String newState = nbx + "," + nby + "," + bx + "," + by;
                if (visited.add(newState)) {
                    queue.offer(new int[]{nbx, nby, bx, by, pushes + 1});
                }
            }
        }
        return -1;
    }

    private boolean inBounds(int x, int y, int m, int n) {
        return x >= 0 && x < m && y >= 0 && y < n;
    }

    // BFS to check if player can reach (tx, ty) from (sx, sy) without crossing the box at (bx, by)
    private boolean canReach(char[][] grid, int sx, int sy, int tx, int ty, int bx, int by) {
        int m = grid.length, n = grid[0].length;
        boolean[][] visited = new boolean[m][n];
        Queue<int[]> queue = new ArrayDeque<>();
        queue.offer(new int[]{sx, sy});
        visited[sx][sy] = true;
        int[][] dirs = {{0,1},{0,-1},{1,0},{-1,0}};
        while (!queue.isEmpty()) {
            int[] curr = queue.poll();
            if (curr[0] == tx && curr[1] == ty) return true;
            for (int[] d : dirs) {
                int nx = curr[0] + d[0], ny = curr[1] + d[1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n &&
                    !visited[nx][ny] && grid[nx][ny] != '#' &&
                    !(nx == bx && ny == by)) {
                    visited[nx][ny] = true;
                    queue.offer(new int[]{nx, ny});
                }
            }
        }
        return false;
    }
}
