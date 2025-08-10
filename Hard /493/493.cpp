class Solution {
public:
    int reversePairs(vector<int>& nums) {
        return mergeSort(nums, 0, nums.size());
    }
    
    int mergeSort(vector<int>& nums, int left, int right) {
        if (right - left <= 1) return 0;
        int mid = left + (right - left) / 2;
        int count = mergeSort(nums, left, mid) + mergeSort(nums, mid, right);
        int j = mid;
        for (int i = left; i < mid; ++i) {
            while (j < right && (long long)nums[i] > 2LL * nums[j]) ++j;
            count += j - mid;
        }
        // Merge step
        vector<int> temp;
        int p = left, q = mid;
        while (p < mid && q < right) {
            if (nums[p] <= nums[q]) temp.push_back(nums[p++]);
            else temp.push_back(nums[q++]);
        }
        while (p < mid) temp.push_back(nums[p++]);
        while (q < right) temp.push_back(nums[q++]);
        for (int i = left; i < right; ++i)
            nums[i] = temp[i - left];
        return count;
    }
};
