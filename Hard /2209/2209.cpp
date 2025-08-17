class Solution {
public:
    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) {
        int n = floor.size();
        vector<vector<int>> dp(n + 1, vector<int>(numCarpets + 1, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int k = 0; k <= numCarpets; ++k) {
                int leave = (floor[i] == '1' ? 1 : 0) + dp[i + 1][k];
                int cover = k > 0 ? dp[min(n, i + carpetLen)][k - 1] : INT_MAX;
                dp[i][k] = min(leave, cover);
            }
        }
        return dp[0][numCarpets];
    }
};
