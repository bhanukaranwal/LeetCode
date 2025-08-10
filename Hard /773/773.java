import java.util.*;

class Solution {
    public int slidingPuzzle(int[][] board) {
        String target = "123450";
        StringBuilder sb = new StringBuilder();
        for (int[] row : board)
            for (int num : row)
                sb.append(num);
        String start = sb.toString();

        // Neighbor indices for each position in the 1D string
        int[][] neighbors = {
            {1, 3},      // 0
            {0, 2, 4},   // 1
            {1, 5},      // 2
            {0, 4},      // 3
            {1, 3, 5},   // 4
            {2, 4}       // 5
        };

        Queue<String> queue = new ArrayDeque<>();
        Set<String> seen = new HashSet<>();
        queue.offer(start);
        seen.add(start);

        int steps = 0;
        while (!queue.isEmpty()) {
            int size = queue.size();
            for (int s = 0; s < size; ++s) {
                String curr = queue.poll();
                if (curr.equals(target)) return steps;
                int zero = curr.indexOf('0');
                for (int nei : neighbors[zero]) {
                    char[] arr = curr.toCharArray();
                    // Swap zero and neighbor
                    arr[zero] = arr[nei];
                    arr[nei] = '0';
                    String next = new String(arr);
                    if (seen.add(next)) {
                        queue.offer(next);
                    }
                }
            }
            steps++;
        }
        return -1;
    }
}
