class Solution {
public:
    int findRotateSteps(string ring, string key) {
        int n = ring.size(), m = key.size();
        // Map each character to all its indices in ring
        unordered_map<char, vector<int>> char_pos;
        for (int i = 0; i < n; ++i)
            char_pos[ring[i]].push_back(i);

        // Memoization: dp[pos in ring][pos in key]
        vector<vector<int>> dp(n, vector<int>(m, -1));

        // Helper to compute distance between two positions on the ring
        auto dist = [&](int a, int b) {
            return min(abs(a - b), n - abs(a - b));
        };

        function<int(int, int)> dfs = [&](int ring_pos, int key_pos) -> int {
            if (key_pos == m) return 0;
            if (dp[ring_pos][key_pos] != -1) return dp[ring_pos][key_pos];
            int res = INT_MAX;
            for (int idx : char_pos[key[key_pos]]) {
                int step = dist(ring_pos, idx) + 1; // +1 for pressing the button
                res = min(res, step + dfs(idx, key_pos + 1));
            }
            return dp[ring_pos][key_pos] = res;
        };

        return dfs(0, 0);
    }
};
