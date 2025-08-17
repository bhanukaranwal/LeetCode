class Solution {
public:
    long long countPairs(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        long long res = 0;
        for (int x : nums) {
            int g = gcd(x, k);
            for (auto& [d, cnt] : freq)
                if ((long long)g * d % k == 0)
                    res += cnt;
            freq[g]++;
        }
        return res;
    }
    int gcd(int a, int b) {
        while (b) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
};
