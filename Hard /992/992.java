class Solution {
    public int subarraysWithKDistinct(int[] nums, int k) {
        return atMostK(nums, k) - atMostK(nums, k - 1);
    }

    // Helper: count subarrays with at most K distinct integers
    private int atMostK(int[] nums, int K) {
        int n = nums.length, left = 0, res = 0;
        int[] count = new int[n + 1];
        int unique = 0;
        for (int right = 0; right < n; ++right) {
            if (count[nums[right]] == 0) unique++;
            count[nums[right]]++;
            while (unique > K) {
                count[nums[left]]--;
                if (count[nums[left]] == 0) unique--;
                left++;
            }
            res += right - left + 1;
        }
        return res;
    }
}
