class Solution {
    public int[] maxSumOfThreeSubarrays(int[] nums, int k) {
        int n = nums.length;
        int[] sum = new int[n + 1];
        for (int i = 0; i < n; i++) sum[i + 1] = sum[i] + nums[i];
        int[] left = new int[n], right = new int[n];
        int total = sum[k] - sum[0], best = 0;
        for (int i = k; i < n; i++) {
            if (sum[i + 1] - sum[i + 1 - k] > total) {
                left[i] = i + 1 - k;
                total = sum[i + 1] - sum[i + 1 - k];
            } else {
                left[i] = left[i - 1];
            }
        }
        total = sum[n] - sum[n - k];
        right[n - k] = n - k;
        for (int i = n - k - 1; i >= 0; i--) {
            if (sum[i + k] - sum[i] >= total) {
                right[i] = i;
                total = sum[i + k] - sum[i];
            } else {
                right[i] = right[i + 1];
            }
        }
        int[] res = new int[3];
        int maxSum = 0;
        for (int i = k; i <= n - 2 * k; i++) {
            int l = left[i - 1], r = right[i + k];
            int cur = (sum[l + k] - sum[l]) + (sum[i + k] - sum[i]) + (sum[r + k] - sum[r]);
            if (cur > maxSum) {
                maxSum = cur;
                res[0] = l;
                res[1] = i;
                res[2] = r;
            }
        }
        return res;
    }
}
