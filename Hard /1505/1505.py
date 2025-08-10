from sortedcontainers import SortedList
from collections import deque

class Solution(object):
    def minInteger(self, num, k):
        n = len(num)
        pos = [deque() for _ in range(10)]
        for i, c in enumerate(num):
            pos[int(c)].append(i)
        removed = SortedList()
        res = []
        for _ in range(n):
            for d in range(10):
                if pos[d]:
                    idx = pos[d][0]
                    shifts = removed.bisect_left(idx)
                    cost = idx - shifts
                    if cost <= k:
                        k -= cost
                        res.append(str(d))
                        removed.add(idx)
                        pos[d].popleft()
                        break
        return ''.join(res)
