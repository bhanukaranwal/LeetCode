class Solution(object):
    def minTrioDegree(self, n, edges):
        # Build adjacency matrix for fast lookup and degree array
        adj = [[False] * (n+1) for _ in range(n+1)]
        degree = [0] * (n+1)
        for u, v in edges:
            adj[u][v] = adj[v][u] = True
            degree[u] += 1
            degree[v] += 1

        res = float('inf')
        # Try all trios (i < j < k)
        for i in range(1, n+1):
            for j in range(i+1, n+1):
                if not adj[i][j]: continue
                for k in range(j+1, n+1):
                    if adj[i][k] and adj[j][k]:
                        # Trio found
                        deg = degree[i] + degree[j] + degree[k] - 6
                        res = min(res, deg)
        return res if res != float('inf') else -1
