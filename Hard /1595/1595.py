class Solution(object):
    def connectTwoGroups(self, cost):
        m, n = len(cost), len(cost[0])
        INF = float('inf')
        dp = [ [INF] * (1 << n) for _ in range(m + 1) ]
        dp[0][0] = 0

        for i in range(m):
            for mask in range(1 << n):
                if dp[i][mask] == INF:
                    continue
                for j in range(n):
                    new_mask = mask | (1 << j)
                    dp[i+1][new_mask] = min(
                        dp[i+1][new_mask],
                        dp[i][mask] + cost[i][j]
                    )

        # After connecting all group 1 points, ensure every group 2 point is connected
        res = INF
        for mask in range(1 << n):
            if dp[m][mask] == INF:
                continue
            # For group 2 points not yet connected, connect them to the cheapest group 1 point
            extra = 0
            for j in range(n):
                if not (mask & (1 << j)):
                    extra += min(cost[i][j] for i in range(m))
            res = min(res, dp[m][mask] + extra)
        return res
