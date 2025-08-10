class Solution {
    public int maxDotProduct(int[] nums1, int[] nums2) {
        int n = nums1.length, m = nums2.length;
        int[][] dp = new int[n + 1][m + 1];
        // Initialize with a very small number to handle negative-only arrays
        for (int i = 0; i <= n; i++) java.util.Arrays.fill(dp[i], Integer.MIN_VALUE);

        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                int prod = nums1[i - 1] * nums2[j - 1];
                // 1. Take both current elements (start new or extend previous)
                dp[i][j] = Math.max(dp[i][j], prod);
                if (dp[i - 1][j - 1] != Integer.MIN_VALUE) {
                    dp[i][j] = Math.max(dp[i][j], dp[i - 1][j - 1] + prod);
                }
                // 2. Skip one from nums1 or nums2
                dp[i][j] = Math.max(dp[i][j], dp[i - 1][j]);
                dp[i][j] = Math.max(dp[i][j], dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }
}
