class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0]*n
        self.sets = n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        xr, yr = self.find(x), self.find(y)
        if xr == yr:
            return False
        if self.rank[xr] < self.rank[yr]:
            self.parent[xr] = yr
        else:
            self.parent[yr] = xr
            if self.rank[xr] == self.rank[yr]:
                self.rank[xr] += 1
        self.sets -= 1
        return True

class Solution(object):
    def maxNumEdgesToRemove(self, n, edges):
        # 0-based indexing for DSU
        alice = DSU(n)
        bob = DSU(n)
        res = 0

        # Type 3 edges first (shared)
        for t, u, v in edges:
            if t == 3:
                # If both can use, try to merge in both
                mergedA = alice.union(u-1, v-1)
                mergedB = bob.union(u-1, v-1)
                if not mergedA and not mergedB:
                    res += 1  # Redundant

        # Type 1 (Alice only)
        for t, u, v in edges:
            if t == 1:
                if not alice.union(u-1, v-1):
                    res += 1  # Redundant

        # Type 2 (Bob only)
        for t, u, v in edges:
            if t == 2:
                if not bob.union(u-1, v-1):
                    res += 1  # Redundant

        # Both must be fully connected (one set)
        if alice.sets > 1 or bob.sets > 1:
            return -1
        return res
