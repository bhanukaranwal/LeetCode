class Solution {
public:
    long long minimumDifference(vector<int>& nums) {
        int n = nums.size() / 3;
        vector<long long> leftMin(2 * n + 1), rightMax(2 * n + 1);
        priority_queue<int> leftHeap;
        priority_queue<int, vector<int>, greater<int>> rightHeap;
        long long sumLeft = 0, sumRight = 0;
        // Compute leftMin: min sum of n elements from the left for each prefix
        for (int i = 0; i < 2 * n; ++i) {
            sumLeft += nums[i];
            leftHeap.push(nums[i]);
            if (leftHeap.size() > n) {
                sumLeft -= leftHeap.top();
                leftHeap.pop();
            }
            if (leftHeap.size() == n) leftMin[i] = sumLeft;
            else leftMin[i] = LLONG_MAX;
        }
        // Compute rightMax: max sum of n elements from the right for each suffix
        for (int i = 3 * n - 1; i >= n; --i) {
            sumRight += nums[i];
            rightHeap.push(nums[i]);
            if (rightHeap.size() > n) {
                sumRight -= rightHeap.top();
                rightHeap.pop();
            }
            if (rightHeap.size() == n) rightMax[i - n] = sumRight;
            else rightMax[i - n] = LLONG_MIN;
        }
        long long res = LLONG_MAX;
        for (int i = n - 1; i < 2 * n; ++i) {
            if (leftMin[i] != LLONG_MAX && rightMax[i - n + 1] != LLONG_MIN)
                res = min(res, leftMin[i] - rightMax[i - n + 1]);
        }
        return res;
    }
};
