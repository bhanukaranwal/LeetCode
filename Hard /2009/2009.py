class Solution(object):
    def minOperations(self, nums):
        n = len(nums)
        unique = sorted(set(nums))
        max_keep = 0
        left = 0
        for right in range(len(unique)):
            # Keep window of size <= n
            while unique[right] - unique[left] >= n:
                left += 1
            max_keep = max(max_keep, right - left + 1)
        return n - max_keep
