import java.util.Arrays;

class Solution {
    public int minCost(int n, int[] cuts) {
        int m = cuts.length;
        int[] allCuts = new int[m + 2];
        allCuts[0] = 0;
        allCuts[m + 1] = n;
        System.arraycopy(cuts, 0, allCuts, 1, m);
        Arrays.sort(allCuts);

        // dp[i][j] = min cost to cut stick from allCuts[i] to allCuts[j]
        int[][] dp = new int[m + 2][m + 2];

        for (int len = 2; len <= m + 1; len++) { // interval length
            for (int i = 0; i + len <= m + 1; i++) {
                int j = i + len;
                dp[i][j] = Integer.MAX_VALUE;
                for (int k = i + 1; k < j; k++) {
                    dp[i][j] = Math.min(dp[i][j],
                        dp[i][k] + dp[k][j] + allCuts[j] - allCuts[i]);
                }
                if (dp[i][j] == Integer.MAX_VALUE) dp[i][j] = 0;
            }
        }
        return dp[0][m + 1];
    }
}
