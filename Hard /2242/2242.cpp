class Solution {
public:
    int maximumScore(vector<int>& scores, vector<vector<int>>& edges) {
        int n = scores.size();
        // For each node, keep top 3 neighbors with highest scores
        vector<vector<int>> best(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            best[u].push_back(v);
            best[v].push_back(u);
        }
        // Sort and keep only top 3 neighbors for each node
        for (int i = 0; i < n; ++i) {
            sort(best[i].begin(), best[i].end(), [&](int a, int b) {
                return scores[a] > scores[b];
            });
            if (best[i].size() > 3) best[i].resize(3);
        }
        int res = -1;
        // Try every edge as the middle of the path (u-v)
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            for (int a : best[u]) {
                if (a == v) continue;
                for (int b : best[v]) {
                    if (b == u || b == a) continue;
                    res = max(res, scores[a] + scores[u] + scores[v] + scores[b]);
                }
            }
        }
        return res;
    }
};
