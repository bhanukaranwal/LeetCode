class Solution(object):
    def minMoves(self, nums, k):
        # Collect indices of all 1's
        ones = [i for i, v in enumerate(nums) if v == 1]
        pre = [0]
        for x in ones:
            pre.append(pre[-1] + x)
        res = float('inf')
        n = len(ones)
        for i in range(n - k + 1):
            mid = i + k // 2
            median = ones[mid]
            # Left cost
            left = median * (mid - i) - (pre[mid] - pre[i])
            # Right cost
            right = (pre[i + k] - pre[mid + 1]) - median * (i + k - mid - 1)
            res = min(res, left + right)
        # Correction for overlapping swaps
        if k % 2 == 0:
            res -= (k // 2) * ((k + 1) // 2)
        else:
            res -= (k // 2) * ((k // 2) + 1)
        return res
