import java.util.*;

class Solution {
    public List<String> maxNumOfSubstrings(String s) {
        int n = s.length();
        int[] left = new int[26], right = new int[26];
        Arrays.fill(left, n);
        Arrays.fill(right, -1);

        // Step 1: Find the first and last occurrence of each character
        for (int i = 0; i < n; i++) {
            int c = s.charAt(i) - 'a';
            left[c] = Math.min(left[c], i);
            right[c] = Math.max(right[c], i);
        }

        // Step 2: For each character, try to expand its interval to include all chars within
        List<int[]> intervals = new ArrayList<>();
        for (int c = 0; c < 26; c++) {
            if (left[c] == n) continue;
            int l = left[c], r = right[c];
            boolean valid = true;
            for (int i = l; i <= r; i++) {
                int cc = s.charAt(i) - 'a';
                if (left[cc] < l) {
                    valid = false;
                    break;
                }
                r = Math.max(r, right[cc]);
            }
            if (valid) intervals.add(new int[]{l, r});
        }

        // Step 3: Greedily select non-overlapping intervals with smallest right
        Collections.sort(intervals, (a, b) -> a[1] - b[1]);
        List<String> res = new ArrayList<>();
        int lastEnd = -1;
        for (int[] interval : intervals) {
            if (interval[0] > lastEnd) {
                res.add(s.substring(interval[0], interval[1] + 1));
                lastEnd = interval[1];
            }
        }
        return res;
    }
}
