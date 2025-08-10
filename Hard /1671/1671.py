class Solution(object):
    def minimumMountainRemovals(self, nums):
        n = len(nums)
        # Compute LIS ending at each index
        LIS = [1] * n
        for i in range(n):
            for j in range(i):
                if nums[j] < nums[i]:
                    LIS[i] = max(LIS[i], LIS[j] + 1)
        # Compute LDS starting at each index
        LDS = [1] * n
        for i in range(n-1, -1, -1):
            for j in range(n-1, i, -1):
                if nums[j] < nums[i]:
                    LDS[i] = max(LDS[i], LDS[j] + 1)
        # Find the maximum mountain length
        res = n
        for i in range(1, n-1):
            if LIS[i] > 1 and LDS[i] > 1:
                res = min(res, n - (LIS[i] + LDS[i] - 1))
        return res
