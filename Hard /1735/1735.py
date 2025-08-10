MOD = 10**9 + 7

class Solution(object):
    def waysToFillArray(self, queries):
        # Precompute factorials up to 2*10^4 for combinations
        N = 20000
        fact = [1] * (N+1)
        inv = [1] * (N+1)
        for i in range(1, N+1):
            fact[i] = fact[i-1] * i % MOD
        inv[N] = pow(fact[N], MOD-2, MOD)
        for i in range(N-1, -1, -1):
            inv[i] = inv[i+1] * (i+1) % MOD

        def comb(a, b):
            if b < 0 or b > a: return 0
            return fact[a] * inv[b] % MOD * inv[a-b] % MOD

        # Factorize k
        def prime_factors(k):
            res = []
            d = 2
            while d * d <= k:
                cnt = 0
                while k % d == 0:
                    k //= d
                    cnt += 1
                if cnt > 0:
                    res.append(cnt)
                d += 1
            if k > 1:
                res.append(1)
            return res

        ans = []
        for n, k in queries:
            pf = prime_factors(k)
            ways = 1
            for cnt in pf:
                ways = ways * comb(cnt + n - 1, n - 1) % MOD
            ans.append(ways)
        return ans
