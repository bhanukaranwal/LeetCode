class Solution {
    public int minKBitFlips(int[] nums, int k) {
        int n = nums.length;
        int flips = 0, curFlip = 0;
        int[] isFlipped = new int[n];

        for (int i = 0; i < n; ++i) {
            if (i >= k) curFlip ^= isFlipped[i - k];
            // If current bit (after all flips so far) is 0, we must flip here
            if ((nums[i] ^ curFlip) == 0) {
                if (i + k > n) return -1;
                isFlipped[i] = 1;
                curFlip ^= 1;
                flips++;
            }
        }
        return flips;
    }
}
