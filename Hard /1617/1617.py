from collections import deque, defaultdict

class Solution(object):
    def countSubgraphsForEachDiameter(self, n, edges):
        # Build adjacency list
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u-1].append(v-1)
            g[v-1].append(u-1)
        
        res = [0] * (n-1)
        
        # Enumerate all subsets with at least 2 nodes
        for mask in range(1, 1 << n):
            nodes = [i for i in range(n) if (mask >> i) & 1]
            if len(nodes) < 2:
                continue
            # Check if the subset is connected (BFS)
            vis = set()
            q = deque([nodes[0]])
            vis.add(nodes[0])
            while q:
                u = q.popleft()
                for v in g[u]:
                    if v in vis: continue
                    if not ((mask >> v) & 1): continue
                    vis.add(v)
                    q.append(v)
            if len(vis) != len(nodes):
                continue  # not connected
            
            # Find diameter: BFS from each node in the subset
            max_d = 0
            for start in nodes:
                dist = [-1] * n
                dist[start] = 0
                q = deque([start])
                while q:
                    u = q.popleft()
                    for v in g[u]:
                        if dist[v] == -1 and ((mask >> v) & 1):
                            dist[v] = dist[u] + 1
                            q.append(v)
                max_d = max(max_d, max([dist[i] for i in nodes]))
            if max_d > 0:
                res[max_d-1] += 1
        return res
