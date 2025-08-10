class Solution {
    public int numSubmatrixSumTarget(int[][] matrix, int target) {
        int m = matrix.length, n = matrix[0].length;
        int res = 0;

        // Iterate over all pairs of rows
        for (int top = 0; top < m; top++) {
            int[] colSum = new int[n];
            for (int bottom = top; bottom < m; bottom++) {
                // Update column sums between top and bottom rows
                for (int col = 0; col < n; col++) {
                    colSum[col] += matrix[bottom][col];
                }
                // Count subarrays in colSum with sum == target
                res += countSubarraysWithSum(colSum, target);
            }
        }
        return res;
    }

    private int countSubarraysWithSum(int[] nums, int target) {
        Map<Integer, Integer> prefixSumCount = new HashMap<>();
        prefixSumCount.put(0, 1);
        int sum = 0, count = 0;
        for (int num : nums) {
            sum += num;
            count += prefixSumCount.getOrDefault(sum - target, 0);
            prefixSumCount.put(sum, prefixSumCount.getOrDefault(sum, 0) + 1);
        }
        return count;
    }
}
