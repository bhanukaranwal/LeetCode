class Solution {
public:
    int maxEnvelopes(vector<vector<int>>& envelopes) {
        // Sort by width ascending, height descending
        sort(envelopes.begin(), envelopes.end(), [](const vector<int>& a, const vector<int>& b) {
            if (a[0] == b[0]) return a[1] > b[1];
            return a[0] < b[0];
        });
        // Find LIS on heights
        vector<int> dp;
        for (const auto& env : envelopes) {
            int h = env[1];
            auto it = lower_bound(dp.begin(), dp.end(), h);
            if (it == dp.end()) {
                dp.push_back(h);
            } else {
                *it = h;
            }
        }
        return dp.size();
    }
};
