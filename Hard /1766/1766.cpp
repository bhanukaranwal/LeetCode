class Solution {
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        int n = nums.size();
        vector<vector<int>> g(n);
        for (auto& e : edges) {
            g[e[0]].push_back(e[1]);
            g[e[1]].push_back(e[0]);
        }
        vector<vector<int>> coprime(51);
        for (int i = 1; i <= 50; ++i)
            for (int j = 1; j <= 50; ++j)
                if (__gcd(i, j) == 1) coprime[i].push_back(j);
        vector<int> ans(n, -1);
        vector<pair<int, int>> last(51, {-1, -1});
        function<void(int, int, int)> dfs = [&](int u, int p, int depth) {
            int mx = -1, idx = -1;
            for (int v : coprime[nums[u]]) {
                if (last[v].first != -1 && last[v].second > mx) {
                    mx = last[v].second;
                    idx = last[v].first;
                }
            }
            ans[u] = idx;
            auto prev = last[nums[u]];
            last[nums[u]] = {u, depth};
            for (int v : g[u]) {
                if (v != p) dfs(v, u, depth + 1);
            }
            last[nums[u]] = prev;
        };
        dfs(0, -1, 0);
        return ans;
    }
};
