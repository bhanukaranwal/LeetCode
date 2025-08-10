class Solution {
public:
    int maxBuilding(int n, vector<vector<int>>& restrictions) {
        // Add building 1 and n as "virtual" restrictions
        restrictions.push_back({1, 0});
        if (restrictions.empty() || restrictions.back()[0] != n)
            restrictions.push_back({n, n - 1});
        sort(restrictions.begin(), restrictions.end());

        // Left-to-right: propagate restrictions
        for (int i = 1; i < restrictions.size(); ++i) {
            int dist = restrictions[i][0] - restrictions[i - 1][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i - 1][1] + dist);
        }
        // Right-to-left: propagate restrictions
        for (int i = restrictions.size() - 2; i >= 0; --i) {
            int dist = restrictions[i + 1][0] - restrictions[i][0];
            restrictions[i][1] = min(restrictions[i][1], restrictions[i + 1][1] + dist);
        }

        int ans = 0;
        for (int i = 1; i < restrictions.size(); ++i) {
            int l = restrictions[i - 1][0], r = restrictions[i][0];
            int hl = restrictions[i - 1][1], hr = restrictions[i][1];
            // The highest possible between l and r is the peak of the "V" between hl and hr
            int peak = (hl + hr + r - l) / 2;
            ans = max(ans, peak);
        }
        return ans;
    }
};
