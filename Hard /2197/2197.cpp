class Solution {
public:
    vector<int> replaceNonCoprimes(vector<int>& nums) {
        vector<int> stk;
        for (int x : nums) {
            while (!stk.empty()) {
                int g = gcd(stk.back(), x);
                if (g == 1) break;
                x = lcm(stk.back(), x);
                stk.pop_back();
            }
            stk.push_back(x);
        }
        return stk;
    }
    int gcd(int a, int b) {
        while (b) {
            int t = a % b;
            a = b;
            b = t;
        }
        return a;
    }
    long long lcm(int a, int b) {
        return 1LL * a / gcd(a, b) * b;
    }
};
