class Solution {
public:
    int nthMagicalNumber(int n, int a, int b) {
        long mod = 1e9 + 7;
        long l = 1, r = 1LL * n * min(a, b);
        long lcm = a / gcd(a, b) * (long)b;
        while (l < r) {
            long m = l + (r - l) / 2;
            if (m / a + m / b - m / lcm < n) l = m + 1;
            else r = m;
        }
        return l % mod;
    }
    long gcd(long x, long y) {
        while (y) {
            long t = y;
            y = x % y;
            x = t;
        }
        return x;
    }
};
