class Solution {
public:
    int maxScore(vector<int>& nums) {
        int n = nums.size(), N = 1 << n;
        vector<int> dp(N, 0);
        vector<vector<int>> gcds(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                gcds[i][j] = gcd(nums[i], nums[j]);
        for (int mask = 0; mask < N; ++mask) {
            int cnt = __builtin_popcount(mask);
            if (cnt % 2) continue;
            for (int i = 0; i < n; ++i) {
                if (!(mask & (1 << i))) continue;
                for (int j = i + 1; j < n; ++j) {
                    if (!(mask & (1 << j))) continue;
                    int newMask = mask ^ (1 << i) ^ (1 << j);
                    dp[mask] = max(dp[mask], dp[newMask] + (cnt / 2) * gcds[i][j]);
                }
            }
        }
        return dp[N - 1];
    }
};
