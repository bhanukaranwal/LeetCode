class Solution(object):
    def maxNumber(self, nums1, nums2, k):
        def pick_max(nums, t):
            stack = []
            drop = len(nums) - t
            for num in nums:
                while drop and stack and stack[-1] < num:
                    stack.pop()
                    drop -= 1
                stack.append(num)
            return stack[:t]
        
        def merge(a, b):
            # Greedily merge two lists to form the largest possible number
            res = []
            while a or b:
                # Compare remaining a and b lexicographically
                if a > b:
                    res.append(a[0])
                    a = a[1:]
                else:
                    res.append(b[0])
                    b = b[1:]
            return res
        
        m, n = len(nums1), len(nums2)
        best = []
        for i in range(max(0, k-n), min(k, m)+1):
            pick1 = pick_max(nums1, i)
            pick2 = pick_max(nums2, k-i)
            candidate = merge(pick1, pick2)
            if candidate > best:
                best = candidate
        return best
