import java.util.*;

class Solution {
    public int[] movesToStamp(String stamp, String target) {
        char[] S = target.toCharArray();
        char[] T = stamp.toCharArray();
        int n = S.length, m = T.length;
        boolean[] visited = new boolean[n];
        List<Integer> res = new ArrayList<>();
        int stars = 0;

        while (stars < n) {
            boolean doneStamp = false;
            for (int i = 0; i <= n - m; ++i) {
                if (!visited[i] && canUnstamp(S, T, i)) {
                    stars += doUnstamp(S, m, i);
                    visited[i] = true;
                    res.add(i);
                    doneStamp = true;
                    if (stars == n) break;
                }
            }
            if (!doneStamp) return new int[0];
        }

        // Reverse the result to get the correct stamping order
        Collections.reverse(res);
        return res.stream().mapToInt(i -> i).toArray();
    }

    // Check if we can unstamp at position i
    private boolean canUnstamp(char[] S, char[] T, int pos) {
        boolean found = false;
        for (int j = 0; j < T.length; ++j) {
            if (S[pos + j] == '?') continue;
            if (S[pos + j] != T[j]) return false;
            found = true;
        }
        return found;
    }

    // Do the unstamp and return how many new '?' we made
    private int doUnstamp(char[] S, int m, int pos) {
        int count = 0;
        for (int j = 0; j < m; ++j) {
            if (S[pos + j] != '?') {
                S[pos + j] = '?';
                count++;
            }
        }
        return count;
    }
}
