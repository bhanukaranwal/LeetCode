class Solution {
    public int minDeletionSize(String[] strs) {
        int n = strs.length, m = strs[0].length();
        int[] dp = new int[m];
        int maxLen = 1;

        // dp[j]: length of the longest sequence ending at column j
        for (int j = 0; j < m; ++j) {
            dp[j] = 1; // At least column j itself
            for (int i = 0; i < j; ++i) {
                boolean canExtend = true;
                for (int row = 0; row < n; ++row) {
                    if (strs[row].charAt(i) > strs[row].charAt(j)) {
                        canExtend = false;
                        break;
                    }
                }
                if (canExtend) {
                    dp[j] = Math.max(dp[j], dp[i] + 1);
                }
            }
            maxLen = Math.max(maxLen, dp[j]);
        }
        // Minimum deletions = total columns - length of longest valid sequence
        return m - maxLen;
    }
}
