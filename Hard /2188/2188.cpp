class Solution {
public:
    int minimumFinishTime(vector<vector<int>>& tires, int changeTime, int numLaps) {
        int inf = 1e9;
        vector<int> minTime(numLaps + 1, inf);
        for (auto& t : tires) {
            int f = t[0], r = t[1];
            long long time = f, sum = f;
            minTime[1] = min(minTime[1], f);
            for (int lap = 2; lap <= numLaps; ++lap) {
                time *= r;
                if (time > f + changeTime) break;
                sum += time;
                if (sum > 1LL * inf) break;
                minTime[lap] = min(minTime[lap], (int)sum);
            }
        }
        vector<int> dp(numLaps + 1, inf);
        dp[0] = 0;
        for (int i = 1; i <= numLaps; ++i) {
            for (int j = 1; j <= i; ++j) {
                if (minTime[j] < inf)
                    dp[i] = min(dp[i], dp[i - j] + minTime[j] + (i == j ? 0 : changeTime));
            }
        }
        return dp[numLaps];
    }
};
