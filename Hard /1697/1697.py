class Solution(object):
    def distanceLimitedPathsExist(self, n, edgeList, queries):
        # Add indices to queries for result ordering
        queries = [q + [i] for i, q in enumerate(queries)]
        # Sort edges and queries by distance/limit
        edgeList.sort(key=lambda x: x[2])
        queries.sort(key=lambda x: x[2])

        # DSU (Union-Find) implementation
        parent = range(n)
        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x
        def union(x, y):
            parent[find(x)] = find(y)

        res = [False] * len(queries)
        i = 0  # Edge pointer
        for p, q, limit, idx in queries:
            # Union all edges with distance < limit
            while i < len(edgeList) and edgeList[i][2] < limit:
                union(edgeList[i][0], edgeList[i][1])
                i += 1
            # Check if p and q are connected
            res[idx] = find(p) == find(q)
        return res
