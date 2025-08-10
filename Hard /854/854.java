import java.util.*;

class Solution {
    public int kSimilarity(String s1, String s2) {
        if (s1.equals(s2)) return 0;
        Queue<String> queue = new ArrayDeque<>();
        Set<String> visited = new HashSet<>();
        queue.offer(s1);
        visited.add(s1);
        int steps = 0;
        int n = s1.length();

        while (!queue.isEmpty()) {
            int size = queue.size();
            steps++;
            for (int i = 0; i < size; ++i) {
                String curr = queue.poll();
                int idx = 0;
                // Find first mismatch
                while (curr.charAt(idx) == s2.charAt(idx)) idx++;
                // Try all swaps that fix the mismatch at idx
                for (int j = idx + 1; j < n; ++j) {
                    if (curr.charAt(j) == s2.charAt(idx) && curr.charAt(j) != s2.charAt(j)) {
                        String next = swap(curr, idx, j);
                        if (next.equals(s2)) return steps;
                        if (visited.add(next)) queue.offer(next);
                    }
                }
            }
        }
        return -1; // Should not happen
    }

    private String swap(String s, int i, int j) {
        char[] arr = s.toCharArray();
        char tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        return new String(arr);
    }
}
