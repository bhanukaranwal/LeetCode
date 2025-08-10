import bisect

class Solution(object):
    def minOperations(self, target, arr):
        # Map values in target to their indices
        pos = {num: i for i, num in enumerate(target)}
        # Build the sequence of indices in arr that are in target
        seq = [pos[a] for a in arr if a in pos]
        # Find LIS in seq
        lis = []
        for x in seq:
            idx = bisect.bisect_left(lis, x)
            if idx == len(lis):
                lis.append(x)
            else:
                lis[idx] = x
        return len(target) - len(lis)
