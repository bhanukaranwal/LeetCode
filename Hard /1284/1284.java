import java.util.*;

class Solution {
    public int minFlips(int[][] mat) {
        int m = mat.length, n = mat[0].length;
        int start = 0;
        // Encode the initial matrix as a bitmask integer
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (mat[i][j] == 1)
                    start |= (1 << (i * n + j));

        if (start == 0) return 0;

        Queue<Integer> queue = new ArrayDeque<>();
        Set<Integer> visited = new HashSet<>();
        queue.offer(start);
        visited.add(start);

        int[][] dirs = {{0,0},{0,1},{0,-1},{1,0},{-1,0}}; // self and 4 neighbors
        int steps = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            while (size-- > 0) {
                int state = queue.poll();
                if (state == 0) return steps;
                // Try flipping each cell
                for (int i = 0; i < m; i++) {
                    for (int j = 0; j < n; j++) {
                        int next = state;
                        for (int[] d : dirs) {
                            int ni = i + d[0], nj = j + d[1];
                            if (ni >= 0 && ni < m && nj >= 0 && nj < n) {
                                next ^= (1 << (ni * n + nj));
                            }
                        }
                        if (!visited.contains(next)) {
                            visited.add(next);
                            queue.offer(next);
                        }
                    }
                }
            }
            steps++;
        }
        return -1;
    }
}
