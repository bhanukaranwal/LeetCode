class Solution(object):
    def numWays(self, words, target):
        MOD = 10**9 + 7
        m, n = len(words[0]), len(target)
        
        # Precompute the count of each character at each position
        from collections import Counter
        count = [Counter() for _ in range(m)]
        for word in words:
            for i, c in enumerate(word):
                count[i][c] += 1

        # dp[i][j]: ways to form target[j:] using words[i:]
        dp = [[0] * (n + 1) for _ in range(m + 1)]
        for i in range(m + 1):
            dp[i][n] = 1  # base case: empty target

        for i in range(m - 1, -1, -1):
            for j in range(n - 1, -1, -1):
                # Option 1: skip this column
                dp[i][j] = dp[i + 1][j]
                # Option 2: use this column if it matches target[j]
                c = target[j]
                if c in count[i]:
                    dp[i][j] = (dp[i][j] + dp[i + 1][j + 1] * count[i][c]) % MOD
        return dp[0][0]
