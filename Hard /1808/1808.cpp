class Solution {
public:
    typedef long long ll;
    const int MOD = 1e9 + 7;
    ll power(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }
    int maxNiceDivisors(int primeFactors) {
        if (primeFactors <= 3) return primeFactors;
        int q = primeFactors / 3, r = primeFactors % 3;
        if (r == 0) return power(3, q) % MOD;
        if (r == 1) return power(3, q - 1) * 4 % MOD;
        return power(3, q) * 2 % MOD;
    }
};
