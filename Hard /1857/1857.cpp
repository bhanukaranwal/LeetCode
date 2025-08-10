class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges) {
        int n = colors.size();
        vector<vector<int>> g(n);
        vector<int> indeg(n, 0);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            indeg[e[1]]++;
        }
        // dp[i][c] = max count of color c on any path ending at node i
        vector<vector<int>> dp(n, vector<int>(26, 0));
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indeg[i] == 0) q.push(i);
        }
        int seen = 0, res = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            seen++;
            dp[u][colors[u] - 'a']++;
            res = max(res, dp[u][colors[u] - 'a']);
            for (int v : g[u]) {
                for (int c = 0; c < 26; ++c) {
                    dp[v][c] = max(dp[v][c], dp[u][c]);
                }
                if (--indeg[v] == 0) q.push(v);
            }
        }
        return seen == n ? res : -1;
    }
};
