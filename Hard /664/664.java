class Solution {
    public int strangePrinter(String s) {
        int n = s.length();
        int[][] dp = new int[n][n];
        for (int l = n - 1; l >= 0; l--) {
            dp[l][l] = 1;
            for (int r = l + 1; r < n; r++) {
                dp[l][r] = dp[l + 1][r] + 1;
                for (int k = l + 1; k <= r; k++) {
                    if (s.charAt(k) == s.charAt(l)) {
                        dp[l][r] = Math.min(dp[l][r], dp[l][k - 1] + dp[k][r] - 1);
                    }
                }
            }
        }
        return dp[0][n - 1];
    }
}
