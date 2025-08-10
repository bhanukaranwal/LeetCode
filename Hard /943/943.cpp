class Solution {
public:
    string shortestSuperstring(vector<string>& words) {
        int n = words.size();
        // Compute overlaps: overlap[i][j] is the max suffix of words[i] matching prefix of words[j]
        vector<vector<int>> overlap(n, vector<int>(n, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) if (i != j) {
                int m = min(words[i].size(), words[j].size());
                for (int k = m; k > 0; --k) {
                    if (words[i].substr(words[i].size() - k) == words[j].substr(0, k)) {
                        overlap[i][j] = k;
                        break;
                    }
                }
            }
        }
        // dp[mask][i]: min length of superstring covering mask, ending with words[i]
        int N = 1 << n;
        vector<vector<int>> dp(N, vector<int>(n, INT_MAX/2));
        vector<vector<int>> parent(N, vector<int>(n, -1));
        for (int i = 0; i < n; ++i) dp[1<<i][i] = words[i].size();

        for (int mask = 1; mask < N; ++mask) {
            for (int last = 0; last < n; ++last) {
                if (!(mask & (1<<last))) continue;
                int prev_mask = mask ^ (1<<last);
                if (prev_mask == 0) continue;
                for (int prev = 0; prev < n; ++prev) {
                    if (!(prev_mask & (1<<prev))) continue;
                    int cand = dp[prev_mask][prev] + (int)words[last].size() - overlap[prev][last];
                    if (cand < dp[mask][last]) {
                        dp[mask][last] = cand;
                        parent[mask][last] = prev;
                    }
                }
            }
        }
        // Find min length ending
        int min_len = INT_MAX, last = -1;
        for (int i = 0; i < n; ++i) {
            if (dp[N-1][i] < min_len) {
                min_len = dp[N-1][i];
                last = i;
            }
        }
        // Reconstruct path
        vector<int> path;
        int mask = N-1;
        while (last != -1) {
            path.push_back(last);
            int tmp = parent[mask][last];
            mask ^= (1<<last);
            last = tmp;
        }
        reverse(path.begin(), path.end());
        // Build answer
        string ans = words[path[0]];
        for (int i = 1; i < path.size(); ++i) {
            int o = overlap[path[i-1]][path[i]];
            ans += words[path[i]].substr(o);
        }
        return ans;
    }
};
