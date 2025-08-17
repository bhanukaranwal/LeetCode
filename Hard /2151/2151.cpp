class Solution {
public:
    int maximumGood(vector<vector<int>>& statements) {
        int n = statements.size(), res = 0;
        for (int mask = 1; mask < (1 << n); ++mask) {
            bool valid = true;
            for (int i = 0; i < n && valid; ++i) {
                if (!(mask & (1 << i))) continue;
                for (int j = 0; j < n; ++j) {
                    if (statements[i][j] == 2) continue;
                    if (statements[i][j] == 1 && !(mask & (1 << j))) valid = false;
                    if (statements[i][j] == 0 && (mask & (1 << j))) valid = false;
                }
            }
            if (valid) res = max(res, __builtin_popcount(mask));
        }
        return res;
    }
};
