class Solution {
public:
    int countDifferentSubsequenceGCDs(vector<int>& nums) {
        int maxNum = *max_element(nums.begin(), nums.end());
        vector<bool> exist(maxNum + 1, false);
        for (int x : nums) exist[x] = true;
        int ans = 0;
        for (int i = 1; i <= maxNum; ++i) {
            int g = 0;
            for (int j = i; j <= maxNum; j += i) {
                if (exist[j]) {
                    g = gcd(g, j);
                    if (g == i) break;
                }
            }
            if (g == i) ++ans;
        }
        return ans;
    }
};
