#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minimumTime(int n, vector<vector<int>>& relations, vector<int>& time) {
        vector<vector<int>> adj(n);
        vector<int> indegree(n, 0);
        for (auto& rel : relations) {
            adj[rel[0] - 1].push_back(rel[1] - 1);
            indegree[rel[1] - 1]++;
        }

        vector<int> finish(n, 0); // finish[i]: earliest finish time for course i
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (indegree[i] == 0) {
                finish[i] = time[i];
                q.push(i);
            }
        }

        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : adj[u]) {
                finish[v] = max(finish[v], finish[u] + time[v]);
                if (--indegree[v] == 0)
                    q.push(v);
            }
        }

        return *max_element(finish.begin(), finish.end());
    }
};
