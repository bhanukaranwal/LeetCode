class Solution(object):
    def maxHeight(self, cuboids):
        # Step 1: Sort dimensions of each cuboid so we can rotate freely
        for c in cuboids:
            c.sort()
        # Step 2: Sort cuboids in decreasing order (so we can use LIS style DP)
        cuboids.sort(reverse=True)
        n = len(cuboids)
        dp = [0] * n
        for i in range(n):
            dp[i] = cuboids[i][2]  # height of the current cuboid (after sorting, index 2 is the largest)
            for j in range(i):
                # If cuboid i can be placed on cuboid j
                if (cuboids[i][0] <= cuboids[j][0] and
                    cuboids[i][1] <= cuboids[j][1] and
                    cuboids[i][2] <= cuboids[j][2]):
                    dp[i] = max(dp[i], dp[j] + cuboids[i][2])
        return max(dp)
