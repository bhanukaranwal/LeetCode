class Solution {
    public int removeBoxes(int[] boxes) {
        int n = boxes.length;
        int[][][] dp = new int[n][n][n];
        return helper(boxes, 0, n - 1, 0, dp);
    }
    private int helper(int[] boxes, int l, int r, int k, int[][][] dp) {
        if (l > r) return 0;
        if (dp[l][r][k] != 0) return dp[l][r][k];
        int origR = r, origK = k;
        while (l < r && boxes[r] == boxes[r - 1]) {
            r--;
            k++;
        }
        int res = helper(boxes, l, r - 1, 0, dp) + (k + 1) * (k + 1);
        for (int i = l; i < r; i++) {
            if (boxes[i] == boxes[r]) {
                res = Math.max(res, helper(boxes, l, i, k + 1, dp) + helper(boxes, i + 1, r - 1, 0, dp));
            }
        }
        dp[l][origR][origK] = res;
        return res;
    }
}
