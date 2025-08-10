import java.util.*;

class Solution {
    public int longestAwesome(String s) {
        int n = s.length();
        int res = 0;
        // Map: mask -> earliest index seen
        Map<Integer, Integer> seen = new HashMap<>();
        seen.put(0, -1); // Empty prefix, all even counts

        int mask = 0;
        for (int i = 0; i < n; i++) {
            // Flip the bit for the current digit
            mask ^= 1 << (s.charAt(i) - '0');

            // Case 1: All digits even (mask seen before)
            if (seen.containsKey(mask)) {
                res = Math.max(res, i - seen.get(mask));
            } else {
                seen.put(mask, i);
            }

            // Case 2: All digits even except one (try flipping each bit)
            for (int d = 0; d < 10; d++) {
                int mask2 = mask ^ (1 << d);
                if (seen.containsKey(mask2)) {
                    res = Math.max(res, i - seen.get(mask2));
                }
            }
        }
        return res;
    }
}
