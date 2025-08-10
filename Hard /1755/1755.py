import bisect

class Solution(object):
    def minAbsDifference(self, nums, goal):
        from itertools import combinations

        def all_sums(arr):
            res = set([0])
            for x in arr:
                res |= {y + x for y in res}
            return sorted(res)

        n = len(nums)
        left = nums[:n//2]
        right = nums[n//2:]

        left_sums = all_sums(left)
        right_sums = all_sums(right)

        ans = float('inf')
        for s in left_sums:
            t = goal - s
            idx = bisect.bisect_left(right_sums, t)
            # Check the closest on the right
            if idx < len(right_sums):
                ans = min(ans, abs(s + right_sums[idx] - goal))
            if idx > 0:
                ans = min(ans, abs(s + right_sums[idx-1] - goal))
        return ans
