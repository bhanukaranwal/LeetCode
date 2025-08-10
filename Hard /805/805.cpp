class Solution {
public:
    bool splitArraySameAverage(vector<int>& nums) {
        int n = nums.size(), total = accumulate(nums.begin(), nums.end(), 0);
        // Early pruning: if not possible for any k, return false
        bool possible = false;
        for (int k = 1; k <= n / 2; ++k) {
            if (total * k % n == 0) {
                possible = true;
                break;
            }
        }
        if (!possible) return false;

        // dp[k] = set of all possible sums using k elements
        vector<unordered_set<int>> dp(n + 1);
        dp[0].insert(0);
        for (int num : nums) {
            for (int k = n / 2; k >= 1; --k) {
                for (int s : dp[k - 1]) {
                    dp[k].insert(s + num);
                }
            }
        }

        for (int k = 1; k <= n / 2; ++k) {
            if ((total * k) % n != 0) continue;
            int target = total * k / n;
            if (dp[k].count(target)) return true;
        }
        return false;
    }
};
