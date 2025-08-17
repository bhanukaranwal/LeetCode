from bisect import bisect_left

class Solution(object):
    def minimumDifference(self, nums):
        n = len(nums) // 2
        left, right = nums[:n], nums[n:]
        total = sum(nums)

        # For each possible pick count, store all possible subset sums
        def get_sums(arr):
            from collections import defaultdict
            res = defaultdict(list)
            L = len(arr)
            for mask in range(1 << L):
                cnt = 0
                s = 0
                for i in range(L):
                    if mask & (1 << i):
                        cnt += 1
                        s += arr[i]
                res[cnt].append(s)
            return res

        left_sums = get_sums(left)
        right_sums = get_sums(right)
        for cnt in right_sums:
            right_sums[cnt].sort()

        answer = float('inf')
        for k in range(n+1):
            left_list = left_sums[k]
            right_list = right_sums[n - k]
            right_list.sort()
            for s in left_list:
                # Want sum as close as possible to half
                target = total // 2 - s
                idx = bisect_left(right_list, target)
                # Try idx and idx-1
                for j in [idx-1, idx]:
                    if 0 <= j < len(right_list):
                        curr = s + right_list[j]
                        diff = abs((total - curr) - curr)
                        answer = min(answer, diff)
        return answer
