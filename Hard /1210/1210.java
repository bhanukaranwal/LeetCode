import java.util.*;

class Solution {
    public int minimumMoves(int[][] grid) {
        int n = grid.length;
        // State: (row, col, orientation), 0 = horizontal, 1 = vertical
        Queue<int[]> q = new ArrayDeque<>();
        // visited[row][col][orientation]
        boolean[][][] visited = new boolean[n][n][2];
        q.offer(new int[]{0, 0, 0, 0}); // row, col, orientation, moves
        visited[0][0][0] = true;

        while (!q.isEmpty()) {
            int[] cur = q.poll();
            int r = cur[0], c = cur[1], o = cur[2], moves = cur[3];
            // Check if reached target
            if (r == n - 1 && c == n - 2 && o == 0) return moves;

            // Move right
            if (o == 0) { // horizontal
                if (c + 2 < n && grid[r][c + 2] == 0 && !visited[r][c + 1][0]) {
                    visited[r][c + 1][0] = true;
                    q.offer(new int[]{r, c + 1, 0, moves + 1});
                }
            } else { // vertical
                if (c + 1 < n && grid[r][c + 1] == 0 && grid[r + 1][c + 1] == 0 && !visited[r][c + 1][1]) {
                    visited[r][c + 1][1] = true;
                    q.offer(new int[]{r, c + 1, 1, moves + 1});
                }
            }

            // Move down
            if (o == 0) { // horizontal
                if (r + 1 < n && grid[r + 1][c] == 0 && grid[r + 1][c + 1] == 0 && !visited[r + 1][c][0]) {
                    visited[r + 1][c][0] = true;
                    q.offer(new int[]{r + 1, c, 0, moves + 1});
                }
            } else { // vertical
                if (r + 2 < n && grid[r + 2][c] == 0 && !visited[r + 1][c][1]) {
                    visited[r + 1][c][1] = true;
                    q.offer(new int[]{r + 1, c, 1, moves + 1});
                }
            }

            // Rotate clockwise (horizontal -> vertical)
            if (o == 0) {
                if (r + 1 < n && grid[r + 1][c] == 0 && grid[r + 1][c + 1] == 0 && !visited[r][c][1]) {
                    visited[r][c][1] = true;
                    q.offer(new int[]{r, c, 1, moves + 1});
                }
            }
            // Rotate counterclockwise (vertical -> horizontal)
            if (o == 1) {
                if (c + 1 < n && grid[r][c + 1] == 0 && grid[r + 1][c + 1] == 0 && !visited[r][c][0]) {
                    visited[r][c][0] = true;
                    q.offer(new int[]{r, c, 0, moves + 1});
                }
            }
        }
        return -1;
    }
}
