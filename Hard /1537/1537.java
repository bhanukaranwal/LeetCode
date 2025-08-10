class Solution {
    public int maxSum(int[] nums1, int[] nums2) {
        final int MOD = 1_000_000_007;
        int n1 = nums1.length, n2 = nums2.length;
        int i = 0, j = 0;
        long sum1 = 0, sum2 = 0, result = 0;

        while (i < n1 && j < n2) {
            if (nums1[i] < nums2[j]) {
                sum1 += nums1[i++];
            } else if (nums1[i] > nums2[j]) {
                sum2 += nums2[j++];
            } else {
                // Intersection point: take the max sum so far and add the common value
                result += Math.max(sum1, sum2) + nums1[i];
                sum1 = 0;
                sum2 = 0;
                i++;
                j++;
            }
        }
        // Add remaining elements
        while (i < n1) sum1 += nums1[i++];
        while (j < n2) sum2 += nums2[j++];

        result += Math.max(sum1, sum2);
        return (int)(result % MOD);
    }
}
