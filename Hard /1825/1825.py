from sortedcontainers import SortedList
from collections import deque

class MKAverage(object):

    def __init__(self, m, k):
        self.m = m
        self.k = k
        self.q = deque()
        self.lo = SortedList()
        self.mid = SortedList()
        self.hi = SortedList()
        self.mid_sum = 0

    def addElement(self, num):
        self.q.append(num)
        if len(self.q) <= self.m:
            self.mid.add(num)
            self.mid_sum += num
            if len(self.q) == self.m:
                # Move k smallest to lo, k largest to hi
                for _ in range(self.k):
                    v = self.mid.pop(0)
                    self.lo.add(v)
                    self.mid_sum -= v
                for _ in range(self.k):
                    v = self.mid.pop(-1)
                    self.hi.add(v)
                    self.mid_sum -= v
        else:
            # Insert new number
            if num <= self.lo[-1]:
                self.lo.add(num)
                v = self.lo.pop(-1)
                self.mid.add(v)
                self.mid_sum += v
            elif num >= self.hi[0]:
                self.hi.add(num)
                v = self.hi.pop(0)
                self.mid.add(v)
                self.mid_sum += v
            else:
                self.mid.add(num)
                self.mid_sum += num
            # Remove oldest number
            old = self.q.popleft()
            if old in self.lo:
                self.lo.remove(old)
                v = self.mid.pop(0)
                self.lo.add(v)
                self.mid_sum -= v
            elif old in self.hi:
                self.hi.remove(old)
                v = self.mid.pop(-1)
                self.hi.add(v)
                self.mid_sum -= v
            else:
                self.mid.remove(old)
                self.mid_sum -= old

    def calculateMKAverage(self):
        if len(self.q) < self.m:
            return -1
        return self.mid_sum // (self.m - 2 * self.k)
