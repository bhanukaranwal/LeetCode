class Solution {
public:
    int res = 1;
    int dfs(int node, vector<vector<int>>& tree, string& s) {
        int max1 = 0, max2 = 0;
        for (int child : tree[node]) {
            int len = dfs(child, tree, s);
            if (s[child] == s[node]) continue;
            if (len > max1) {
                max2 = max1;
                max1 = len;
            } else if (len > max2) {
                max2 = len;
            }
        }
        res = max(res, max1 + max2 + 1);
        return max1 + 1;
    }
    int longestPath(vector<int>& parent, string s) {
        int n = parent.size();
        vector<vector<int>> tree(n);
        for (int i = 1; i < n; ++i)
            tree[parent[i]].push_back(i);
        dfs(0, tree, s);
        return res;
    }
};
