class Solution {
public:
    int maxValueAfterReverse(vector<int>& nums) {
        int n = nums.size();
        int total = 0;
        for (int i = 0; i < n - 1; ++i)
            total += abs(nums[i] - nums[i + 1]);

        int res = total;

        // Case 1: Reverse a subarray that includes the first element
        for (int i = 1; i < n - 1; ++i)
            res = max(res, total + abs(nums[0] - nums[i + 1]) - abs(nums[i] - nums[i + 1]));

        // Case 2: Reverse a subarray that includes the last element
        for (int i = 0; i < n - 1; ++i)
            res = max(res, total + abs(nums[n - 1] - nums[i]) - abs(nums[i] - nums[i + 1]));

        // Case 3: Reverse any subarray inside (not including first or last)
        int min2 = INT_MAX, max2 = INT_MIN;
        for (int i = 0; i < n - 1; ++i) {
            int a = nums[i], b = nums[i + 1];
            min2 = min(min2, max(a, b));
            max2 = max(max2, min(a, b));
        }
        res = max(res, total + 2 * (max2 - min2));

        return res;
    }
};
