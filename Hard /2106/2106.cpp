#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxTotalFruits(vector<vector<int>>& fruits, int startPos, int k) {
        int n = fruits.size();
        vector<int> pos, pre(n+1, 0);
        for (int i = 0; i < n; ++i) {
            pos.push_back(fruits[i][0]);
            pre[i+1] = pre[i] + fruits[i][1];
        }
        int ans = 0;
        // Try all intervals [l, r]
        for (int l = 0, r = 0; l < n; ++l) {
            // Move r as far as possible within k steps
            while (r < n) {
                int left = fruits[l][0], right = fruits[r][0];
                // Two ways: left first or right first
                int steps1 = abs(startPos - left) + (right - left);
                int steps2 = abs(startPos - right) + (right - left);
                if (min(steps1, steps2) > k) break;
                ++r;
            }
            ans = max(ans, pre[r] - pre[l]);
        }
        return ans;
    }
};
