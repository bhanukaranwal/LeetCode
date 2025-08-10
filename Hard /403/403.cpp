class Solution {
public:
    bool canCross(vector<int>& stones) {
        unordered_map<int, int> pos_idx;
        for (int i = 0; i < stones.size(); ++i)
            pos_idx[stones[i]] = i;
        int n = stones.size();
        // dp[i][k]: can we reach stone i with last jump k?
        vector<unordered_map<int, bool>> dp(n);

        function<bool(int, int)> dfs = [&](int idx, int k) {
            if (idx == n - 1) return true;
            if (dp[idx].count(k)) return dp[idx][k];
            for (int jump = k - 1; jump <= k + 1; ++jump) {
                if (jump <= 0) continue;
                int next_pos = stones[idx] + jump;
                if (pos_idx.count(next_pos)) {
                    int next_idx = pos_idx[next_pos];
                    if (dfs(next_idx, jump))
                        return dp[idx][k] = true;
                }
            }
            return dp[idx][k] = false;
        };

        // The first jump must be 1 unit
        if (stones[1] != 1) return false;
        return dfs(1, 1);
    }
};
