class Solution {
public:
    int maxValue(vector<vector<int>>& events, int k) {
        sort(events.begin(), events.end());
        int n = events.size();
        vector<vector<int>> dp(n + 1, vector<int>(k + 1, 0));
        
        for (int i = n - 1; i >= 0; --i) {
            int next = i + 1;
            while (next < n && events[next][0] <= events[i][1]) {
                ++next;
            }
            for (int j = 0; j <= k; ++j) {
                dp[i][j] = dp[i + 1][j];
                if (j > 0) {
                    dp[i][j] = max(dp[i][j], events[i][2] + dp[next][j - 1]);
                }
            }
        }
        
        return dp[0][k];
    }
};
