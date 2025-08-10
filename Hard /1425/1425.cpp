class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> dp(n);
        deque<int> dq; // stores indices, dp[dq.front()] is always the max in window

        int res = nums[0];
        for (int i = 0; i < n; ++i) {
            // dp[i]: max sum ending at i
            dp[i] = nums[i];
            if (!dq.empty()) dp[i] = max(dp[i], nums[i] + dp[dq.front()]);
            res = max(res, dp[i]);
            // Maintain decreasing order in dq
            while (!dq.empty() && dp[i] >= dp[dq.back()]) dq.pop_back();
            dq.push_back(i);
            // Remove indices out of window
            if (dq.front() <= i - k) dq.pop_front();
        }
        return res;
    }
};

