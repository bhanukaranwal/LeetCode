class Solution {
public:
    int maximumScore(vector<int>& nums, vector<int>& multipliers) {
        int n = nums.size(), m = multipliers.size();
        vector<int> dp(m + 1, 0);
        for (int i = m - 1; i >= 0; --i) {
            vector<int> next = dp;
            for (int left = i; left >= 0; --left) {
                int right = n - 1 - (i - left);
                dp[left] = max(multipliers[i] * nums[left] + next[left + 1],
                               multipliers[i] * nums[right] + next[left]);
            }
        }
        return dp[0];
    }
};
