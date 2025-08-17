from bisect import bisect_right, bisect_left

class Solution(object):
    def kthSmallestProduct(self, nums1, nums2, k):
        def count_leq(x):
            count = 0
            for a in nums1:
                if a == 0:
                    if x >= 0:
                        count += len(nums2)
                elif a > 0:
                    # b <= x // a
                    cnt = bisect_right(nums2, x // a)
                    count += cnt
                else:
                    # a < 0, want b >= ceil(x / a)
                    # ceil(x / a) = x // a if x % a == 0 else x // a + 1
                    t = x // a
                    if x % a != 0:
                        t += 1
                    cnt = len(nums2) - bisect_left(nums2, t)
                    count += cnt
            return count

        left, right = -10**10, 10**10
        while left < right:
            mid = (left + right) // 2
            if count_leq(mid) < k:
                left = mid + 1
            else:
                right = mid
        return left
