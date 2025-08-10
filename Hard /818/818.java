import java.util.*;

class Solution {
    public int racecar(int target) {
        Queue<int[]> queue = new ArrayDeque<>();
        Set<String> visited = new HashSet<>();
        queue.offer(new int[]{0, 1}); // {position, speed}
        visited.add("0,1");
        int steps = 0;
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int i = 0; i < size; ++i) {
                int[] state = queue.poll();
                int pos = state[0], speed = state[1];
                if (pos == target) return steps;

                // Accelerate
                int nextPos = pos + speed;
                int nextSpeed = speed * 2;
                String key1 = nextPos + "," + nextSpeed;
                // Only consider reasonable bounds
                if (Math.abs(nextPos) <= 2 * target && !visited.contains(key1)) {
                    queue.offer(new int[]{nextPos, nextSpeed});
                    visited.add(key1);
                }

                // Reverse
                int revSpeed = speed > 0 ? -1 : 1;
                String key2 = pos + "," + revSpeed;
                if (!visited.contains(key2)) {
                    queue.offer(new int[]{pos, revSpeed});
                    visited.add(key2);
                }
            }
            steps++;
        }
        return -1; // Should not reach here
    }
}
