class Solution {
public:
    int sumSubseqWidths(vector<int>& nums) {
        int n = nums.size();
        long mod = 1e9 + 7, res = 0;
        sort(nums.begin(), nums.end());
        vector<long> pow2(n, 1);
        for (int i = 1; i < n; ++i)
            pow2[i] = pow2[i-1] * 2 % mod;
        for (int i = 0; i < n; ++i)
            res = (res + (pow2[i] - pow2[n-1-i]) * nums[i]) % mod;
        return (res + mod) % mod;
    }
};
