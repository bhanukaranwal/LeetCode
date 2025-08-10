class Solution {
public:
    bool isGoodArray(vector<int>& nums) {
        int g = nums[0];
        for (int i = 1; i < nums.size(); ++i) {
            g = gcd(g, nums[i]);
            if (g == 1) return true; // Early exit
        }
        return g == 1;
    }
    int gcd(int a, int b) {
        while (b) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }
};
