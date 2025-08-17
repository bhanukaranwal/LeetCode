#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maximalPathQuality(vector<int>& values, vector<vector<int>>& edges, int maxTime) {
        int n = values.size();
        vector<vector<pair<int,int>>> graph(n);
        for (auto& e : edges) {
            graph[e[0]].push_back({e[1], e[2]});
            graph[e[1]].push_back({e[0], e[2]});
        }
        vector<int> visited(n, 0);
        int ans = 0;
        function<void(int, int, int)> dfs = [&](int node, int time, int quality) {
            if (time > maxTime) return;
            if (node == 0) ans = max(ans, quality);
            visited[node]++;
            for (auto& [nei, t] : graph[node]) {
                int add = (visited[nei] == 0 ? values[nei] : 0);
                dfs(nei, time + t, quality + add);
            }
            visited[node]--;
        };
        dfs(0, 0, values[0]);
        return ans;
    }
};
