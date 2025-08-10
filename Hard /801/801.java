class Solution {
    public int minSwap(int[] nums1, int[] nums2) {
        int n = nums1.length;
        // keep: min swaps to make sequences increasing up to i, without swapping at i
        // swap: min swaps to make sequences increasing up to i, with swapping at i
        int keep = 0, swap = 1;
        for (int i = 1; i < n; ++i) {
            int newKeep = Integer.MAX_VALUE, newSwap = Integer.MAX_VALUE;
            // No swap at i
            if (nums1[i] > nums1[i-1] && nums2[i] > nums2[i-1]) {
                newKeep = Math.min(newKeep, keep);
                newSwap = Math.min(newSwap, swap + 1);
            }
            // Swap at i
            if (nums1[i] > nums2[i-1] && nums2[i] > nums1[i-1]) {
                newKeep = Math.min(newKeep, swap);
                newSwap = Math.min(newSwap, keep + 1);
            }
            keep = newKeep;
            swap = newSwap;
        }
        return Math.min(keep, swap);
    }
}
