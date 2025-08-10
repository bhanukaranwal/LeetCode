class Solution {
    public int maxSizeSlices(int[] slices) {
        int n = slices.length, k = n / 3;
        return Math.max(maxSum(slices, 0, n - 2, k), maxSum(slices, 1, n - 1, k));
    }
    private int maxSum(int[] slices, int start, int end, int k) {
        int m = end - start + 1;
        int[][] dp = new int[m + 1][k + 1];
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= k; j++) {
                dp[i][j] = Math.max(dp[i - 1][j], (i >= 2 ? dp[i - 2][j - 1] : 0) + slices[start + i - 1]);
            }
        }
        return dp[m][k];
    }
}
