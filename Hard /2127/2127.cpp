class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        vector<int> indegree(n), dp(n, 1);
        for (int i = 0; i < n; ++i) indegree[favorite[i]]++;
        queue<int> q;
        for (int i = 0; i < n; ++i) if (indegree[i] == 0) q.push(i);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int v = favorite[u];
            dp[v] = max(dp[v], dp[u] + 1);
            if (--indegree[v] == 0) q.push(v);
        }
        int maxCycle = 0, pairSum = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            if (indegree[i] > 0 && !visited[i]) {
                int u = i, len = 0;
                while (!visited[u]) {
                    visited[u] = true;
                    u = favorite[u];
                    len++;
                }
                if (len == 2) {
                    int a = i, b = favorite[i];
                    pairSum += dp[a] + dp[b];
                } else {
                    maxCycle = max(maxCycle, len);
                }
            }
        }
        return max(maxCycle, pairSum);
    }
};
