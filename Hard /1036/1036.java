import java.util.*;

class Solution {
    private static final int BOUND = (int)1e6;
    private static final int[] DIRS = {0, 1, 0, -1, 0};

    public boolean isEscapePossible(int[][] blocked, int[] source, int[] target) {
        Set<Long> blockedSet = new HashSet<>();
        for (int[] b : blocked) {
            blockedSet.add(hash(b[0], b[1]));
        }
        int maxSteps = blocked.length * (blocked.length - 1) / 2;

        return bfs(source, target, blockedSet, maxSteps) && bfs(target, source, blockedSet, maxSteps);
    }

    private boolean bfs(int[] start, int[] finish, Set<Long> blocked, int maxSteps) {
        Set<Long> visited = new HashSet<>();
        Queue<int[]> queue = new ArrayDeque<>();
        queue.offer(start);
        visited.add(hash(start[0], start[1]));

        while (!queue.isEmpty() && visited.size() <= maxSteps) {
            int[] curr = queue.poll();
            for (int d = 0; d < 4; d++) {
                int nx = curr[0] + DIRS[d];
                int ny = curr[1] + DIRS[d + 1];
                if (nx < 0 || nx >= BOUND || ny < 0 || ny >= BOUND) continue;
                long h = hash(nx, ny);
                if (blocked.contains(h) || visited.contains(h)) continue;
                if (nx == finish[0] && ny == finish[1]) return true;
                queue.offer(new int[]{nx, ny});
                visited.add(h);
            }
        }
        // If we visited more than maxSteps, we are not enclosed
        return visited.size() > maxSteps;
    }

    private long hash(int x, int y) {
        return ((long)x << 20) | y;
    }
}
