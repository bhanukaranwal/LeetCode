from collections import deque, defaultdict

class Solution(object):
    def secondMinimum(self, n, edges, time, change):
        # Build graph
        graph = [[] for _ in range(n+1)]
        for u, v in edges:
            graph[u].append(v)
            graph[v].append(u)
        
        # BFS with (current node, current time)
        q = deque()
        q.append((1, 0))
        # For each node, store up to two earliest arrival times
        visited = defaultdict(list)
        visited[1] = [0]
        
        while q:
            node, t = q.popleft()
            for nei in graph[node]:
                # Wait for green if needed
                wait = 0
                if (t // change) % 2 == 1:
                    wait = change - (t % change)
                arrive = t + wait + time
                # Only consider if we haven't recorded this arrival time for nei
                if len(visited[nei]) < 2 and (not visited[nei] or visited[nei][0] != arrive):
                    visited[nei].append(arrive)
                    q.append((nei, arrive))
            # If we've reached node n twice, return the second time
            if len(visited[n]) == 2:
                return visited[n][1]
