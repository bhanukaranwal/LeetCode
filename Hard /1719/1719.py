from collections import defaultdict

class Solution(object):
    def checkWays(self, pairs):
        # Build adjacency sets
        adj = defaultdict(set)
        for x, y in pairs:
            adj[x].add(y)
            adj[y].add(x)
        nodes = list(adj)
        # The root must be connected to all other nodes
        root = None
        n = len(nodes)
        for node in nodes:
            if len(adj[node]) == n - 1:
                root = node
                break
        if root is None:
            return 0

        res = 1
        for node in nodes:
            if node == root:
                continue
            # Parent candidates: node with the smallest degree among neighbors that have more degree than node
            parent = None
            parent_deg = float('inf')
            for nei in adj[node]:
                if len(adj[nei]) >= len(adj[node]) and len(adj[nei]) < parent_deg:
                    parent = nei
                    parent_deg = len(adj[nei])
            if parent is None:
                return 0
            # All neighbors of node except parent must be neighbors of parent
            if not adj[node] - {parent} <= adj[parent]:
                return 0
            if len(adj[parent]) == len(adj[node]):
                res = 2
        return res
