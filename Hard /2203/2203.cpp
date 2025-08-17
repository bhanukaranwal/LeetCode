class Solution {
public:
    using ll = long long;
    vector<ll> dijkstra(int n, vector<vector<pair<int,int>>>& graph, int src) {
        vector<ll> dist(n, LLONG_MAX);
        priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
        dist[src] = 0;
        pq.emplace(0, src);
        while (!pq.empty()) {
            auto [d, u] = pq.top(); pq.pop();
            if (d > dist[u]) continue;
            for (auto& [v, w] : graph[u]) {
                if (dist[v] > d + w) {
                    dist[v] = d + w;
                    pq.emplace(dist[v], v);
                }
            }
        }
        return dist;
    }
    long long minimumWeight(int n, vector<vector<int>>& edges, int src1, int src2, int dest) {
        vector<vector<pair<int,int>>> g(n), rg(n);
        for (auto& e : edges) {
            g[e[0]].emplace_back(e[1], e[2]);
            rg[e[1]].emplace_back(e[0], e[2]);
        }
        vector<ll> d1 = dijkstra(n, g, src1);
        vector<ll> d2 = dijkstra(n, g, src2);
        vector<ll> dd = dijkstra(n, rg, dest);
        ll res = LLONG_MAX;
        for (int i = 0; i < n; ++i) {
            if (d1[i] == LLONG_MAX || d2[i] == LLONG_MAX || dd[i] == LLONG_MAX) continue;
            res = min(res, d1[i] + d2[i] + dd[i]);
        }
        return res == LLONG_MAX ? -1 : res;
    }
};
