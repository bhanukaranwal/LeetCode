class Solution:
    def leastOpsExpressTarget(self, x, target):
        memo = {}
        def dfs(v):
            if x >= v:
                # Option 1: v times x/x (cost: v*2-1)
                # Option 2: x-v times x/x, as x-(x/x)-(x/x)... (cost: (x-v)*2)
                return min(v * 2 - 1, 2 * (x - v))
            if v in memo:
                return memo[v]
            k = 2
            while x ** k < v:
                k += 1
            # Now x**(k-1) < v <= x**k
            left = k - 1 + dfs(v - x ** (k - 1))
            right = float('inf')
            if x ** k - v < v:
                right = k + dfs(x ** k - v)
            memo[v] = min(left, right)
            return memo[v]
        return dfs(target)
