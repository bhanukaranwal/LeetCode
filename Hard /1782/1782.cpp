class Solution {
public:
    vector<int> countPairs(int n, vector<vector<int>>& edges, vector<int>& queries) {
        vector<int> deg(n + 1, 0);
        unordered_map<long long, int> cnt;
        for (auto& e : edges) {
            int u = e[0], v = e[1];
            if (u > v) swap(u, v);
            deg[u]++;
            deg[v]++;
            cnt[(long long)u * 100000 + v]++;
        }
        vector<int> sorted_deg(deg.begin() + 1, deg.end());
        sort(sorted_deg.begin(), sorted_deg.end());
        vector<int> ans;
        for (int q : queries) {
            int res = 0, l = 0, r = n - 1;
            while (l < r) {
                if (sorted_deg[l] + sorted_deg[r] > q) {
                    res += r - l;
                    r--;
                } else l++;
            }
            for (auto& [key, c] : cnt) {
                int u = key / 100000, v = key % 100000;
                if (deg[u] + deg[v] > q && deg[u] + deg[v] - c <= q) res--;
            }
            ans.push_back(res);
        }
        return ans;
    }
};
