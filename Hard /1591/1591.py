class Solution(object):
    def isPrintable(self, grid):
        m, n = len(grid), len(grid[0])
        colors = set()
        # Find bounding box for each color
        minr = [m] * 61
        minc = [n] * 61
        maxr = [-1] * 61
        maxc = [-1] * 61
        for r in range(m):
            for c in range(n):
                color = grid[r][c]
                colors.add(color)
                minr[color] = min(minr[color], r)
                maxr[color] = max(maxr[color], r)
                minc[color] = min(minc[color], c)
                maxc[color] = max(maxc[color], c)

        # Build dependency graph
        from collections import defaultdict, deque
        graph = defaultdict(set)
        indegree = [0] * 61
        for color in colors:
            for r in range(minr[color], maxr[color]+1):
                for c in range(minc[color], maxc[color]+1):
                    other = grid[r][c]
                    if other != color:
                        if other not in graph[color]:
                            graph[color].add(other)
                            indegree[other] += 1

        # Topological sort
        q = deque([color for color in colors if indegree[color] == 0])
        printed = set()
        while q:
            color = q.popleft()
            printed.add(color)
            for nei in graph[color]:
                indegree[nei] -= 1
                if indegree[nei] == 0:
                    q.append(nei)
        return len(printed) == len(colors)
