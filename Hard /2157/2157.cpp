class Solution {
public:
    vector<int> groupStrings(vector<string>& words) {
        unordered_map<int, int> maskCount;
        for (const string& w : words) {
            int mask = 0;
            for (char c : w) mask |= 1 << (c - 'a');
            maskCount[mask]++;
        }
        unordered_map<int, vector<int>> graph;
        for (auto& [mask, _] : maskCount) {
            for (int i = 0; i < 26; ++i) {
                int add = mask | (1 << i);
                int del = mask & ~(1 << i);
                if (add != mask && maskCount.count(add)) graph[mask].push_back(add);
                if (del != mask && maskCount.count(del)) graph[mask].push_back(del);
                if ((mask & (1 << i)) == 0) continue;
                for (int j = 0; j < 26; ++j) {
                    if (i == j) continue;
                    int rep = (mask & ~(1 << i)) | (1 << j);
                    if (rep != mask && maskCount.count(rep)) graph[mask].push_back(rep);
                }
            }
        }
        unordered_set<int> visited;
        int groups = 0, maxSize = 0;
        for (auto& [mask, _] : maskCount) {
            if (visited.count(mask)) continue;
            queue<int> q;
            q.push(mask);
            visited.insert(mask);
            int size = 0;
            while (!q.empty()) {
                int curr = q.front(); q.pop();
                size += maskCount[curr];
                for (int nei : graph[curr]) {
                    if (!visited.count(nei)) {
                        visited.insert(nei);
                        q.push(nei);
                    }
                }
            }
            groups++;
            maxSize = max(maxSize, size);
        }
        return {groups, maxSize};
    }
};
