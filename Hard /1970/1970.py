from collections import deque

class Solution(object):
    def latestDayToCross(self, row, col, cells):
        def can_cross(day):
            grid = [[0] * col for _ in range(row)]
            for i in range(day):
                r, c = cells[i]
                grid[r-1][c-1] = 1
            q = deque()
            for c in range(col):
                if grid[0][c] == 0:
                    q.append((0, c))
                    grid[0][c] = -1  # Mark as visited
            while q:
                r0, c0 = q.popleft()
                if r0 == row - 1:
                    return True
                for dr, dc in [(-1,0),(1,0),(0,-1),(0,1)]:
                    nr, nc = r0 + dr, c0 + dc
                    if 0 <= nr < row and 0 <= nc < col and grid[nr][nc] == 0:
                        grid[nr][nc] = -1
                        q.append((nr, nc))
            return False

        left, right = 1, len(cells)
        ans = 0
        while left <= right:
            mid = (left + right) // 2
            if can_cross(mid):
                ans = mid
                left = mid + 1
            else:
                right = mid - 1
        return ans
