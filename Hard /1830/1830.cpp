class Solution {
public:
    const int MOD = 1e9 + 7;
    vector<long long> fact, invFact;

    long long modPow(long long a, long long b) {
        long long res = 1;
        while (b) {
            if (b & 1) res = res * a % MOD;
            a = a * a % MOD;
            b >>= 1;
        }
        return res;
    }

    void prepare(int n) {
        fact.resize(n+1, 1);
        invFact.resize(n+1, 1);
        for (int i = 1; i <= n; ++i)
            fact[i] = fact[i-1] * i % MOD;
        invFact[n] = modPow(fact[n], MOD-2);
        for (int i = n-1; i >= 0; --i)
            invFact[i] = invFact[i+1] * (i+1) % MOD;
    }

    int makeStringSorted(string s) {
        int n = s.size();
        prepare(n);
        vector<int> cnt(26, 0);
        for (char c : s) cnt[c-'a']++;

        long long ans = 0;
        for (int i = 0; i < n; ++i) {
            int ch = s[i] - 'a';
            for (int c = 0; c < ch; ++c) {
                if (cnt[c] == 0) continue;
                cnt[c]--;
                // Compute number of permutations with cnt
                long long ways = fact[n-i-1];
                for (int j = 0; j < 26; ++j)
                    ways = ways * invFact[cnt[j]] % MOD;
                ans = (ans + ways) % MOD;
                cnt[c]++;
            }
            cnt[ch]--;
        }
        return ans;
    }
};
