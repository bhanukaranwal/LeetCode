class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        int n = graph.size();
        if (n == 1) return 0;
        int all_visited = (1 << n) - 1;
        queue<pair<int, int>> q; // {node, mask}
        vector<vector<bool>> visited(n, vector<bool>(1 << n, false));

        // Start BFS from every node
        for (int i = 0; i < n; ++i) {
            q.push({i, 1 << i});
            visited[i][1 << i] = true;
        }

        int steps = 0;
        while (!q.empty()) {
            int sz = q.size();
            while (sz--) {
                auto [u, mask] = q.front(); q.pop();
                for (int v : graph[u]) {
                    int next_mask = mask | (1 << v);
                    if (next_mask == all_visited) return steps + 1;
                    if (!visited[v][next_mask]) {
                        visited[v][next_mask] = true;
                        q.push({v, next_mask});
                    }
                }
            }
            steps++;
        }
        return -1; // Should never reach here for a connected graph
    }
};
