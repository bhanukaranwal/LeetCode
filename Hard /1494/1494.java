import java.util.*;

class Solution {
    public int minNumberOfSemesters(int n, int[][] relations, int k) {
        int[] prereq = new int[n];
        for (int[] rel : relations) {
            prereq[rel[1] - 1] |= 1 << (rel[0] - 1);
        }
        int N = 1 << n;
        int[] dp = new int[N];
        Arrays.fill(dp, n + 1); // worst case: one course per semester
        dp[0] = 0;

        for (int mask = 0; mask < N; mask++) {
            // Find all courses that can be taken now (prereqs met)
            int canTake = 0;
            for (int i = 0; i < n; i++) {
                if ((mask & (1 << i)) == 0 && (mask & prereq[i]) == prereq[i]) {
                    canTake |= 1 << i;
                }
            }
            // Enumerate all subsets of canTake with up to k bits set
            for (int sub = canTake; sub > 0; sub = (sub - 1) & canTake) {
                if (Integer.bitCount(sub) > k) continue;
                dp[mask | sub] = Math.min(dp[mask | sub], dp[mask] + 1);
            }
        }
        return dp[N - 1];
    }
}
