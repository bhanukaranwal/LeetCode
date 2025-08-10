class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int n = nums.size(), l = k, r = k, mn = nums[k], res = nums[k];
        while (l > 0 || r < n - 1) {
            if (l == 0) r++;
            else if (r == n - 1) l--;
            else if (nums[l - 1] > nums[r + 1]) l--;
            else r++;
            mn = min(mn, min(nums[l], nums[r]));
            res = max(res, mn * (r - l + 1));
        }
        return res;
    }
};
