import java.util.*;

class Solution {
    public int numberWays(List<List<Integer>> hats) {
        int n = hats.size(), MOD = 1_000_000_007;
        // Map each hat to the list of people who like it
        List<Integer>[] hatToPeople = new List[41];
        for (int i = 0; i <= 40; i++) hatToPeople[i] = new ArrayList<>();
        for (int i = 0; i < n; i++)
            for (int h : hats.get(i)) hatToPeople[h].add(i);

        int maxMask = 1 << n;
        int[] dp = new int[maxMask];
        dp[0] = 1; // base case: no one has a hat

        // For each hat, update the ways to assign hats
        for (int hat = 1; hat <= 40; hat++) {
            int[] next = dp.clone();
            for (int mask = 0; mask < maxMask; mask++) {
                if (dp[mask] == 0) continue;
                for (int person : hatToPeople[hat]) {
                    if ((mask & (1 << person)) == 0) {
                        next[mask | (1 << person)] = (next[mask | (1 << person)] + dp[mask]) % MOD;
                    }
                }
            }
            dp = next;
        }
        return dp[maxMask - 1];
    }
}
