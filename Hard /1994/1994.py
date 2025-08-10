class Solution(object):
    def numberOfGoodSubsets(self, nums):
        MOD = 10**9 + 7
        from collections import Counter
        
        primes = [2,3,5,7,11,13,17,19,23,29]
        num_mask = {}
        for x in range(2, 31):
            mask = 0
            n = x
            valid = True
            for i, p in enumerate(primes):
                cnt = 0
                while n % p == 0:
                    n //= p
                    cnt += 1
                if cnt > 1:
                    valid = False
                    break
                if cnt == 1:
                    mask |= (1 << i)
            if valid and n == 1:
                num_mask[x] = mask

        count = Counter(nums)
        dp = [0] * (1 << len(primes))
        dp[0] = 1
        for x in num_mask:
            if count[x] == 0:
                continue
            m = num_mask[x]
            for mask in range((1 << len(primes)) - 1, -1, -1):
                if (mask & m) == 0:
                    dp[mask | m] = (dp[mask | m] + dp[mask] * count[x]) % MOD

        ans = sum(dp[1:]) % MOD  # exclude empty subset
        # Multiply by 2^count[1] for all possible combinations of 1's
        ans = (ans * pow(2, count[1], MOD)) % MOD
        return ans
