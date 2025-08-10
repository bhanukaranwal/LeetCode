from collections import deque

class Solution(object):
    def isTransformable(self, s, t):
        # Store the indices of each digit in s
        pos = [deque() for _ in range(10)]
        for i, ch in enumerate(s):
            pos[int(ch)].append(i)
        
        for ch in t:
            d = int(ch)
            if not pos[d]:
                return False  # No such digit left in s
            idx = pos[d].popleft()
            # Check if any smaller digit is to the left of idx in s
            for smaller in range(d):
                if pos[smaller] and pos[smaller][0] < idx:
                    return False
        return True
