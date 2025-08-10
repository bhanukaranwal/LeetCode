class Solution {
    public int maxChunksToSorted(int[] arr) {
        int n = arr.length;
        int[] rightMin = new int[n + 1];
        rightMin[n] = Integer.MAX_VALUE;
        // Build suffix min array
        for (int i = n - 1; i >= 0; --i) {
            rightMin[i] = Math.min(rightMin[i + 1], arr[i]);
        }
        int res = 0, leftMax = Integer.MIN_VALUE;
        for (int i = 0; i < n; ++i) {
            leftMax = Math.max(leftMax, arr[i]);
            if (leftMax <= rightMin[i + 1]) {
                res++;
            }
        }
        return res;
    }
}
