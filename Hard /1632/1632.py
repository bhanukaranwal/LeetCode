class Solution(object):
    def matrixRankTransform(self, matrix):
        m, n = len(matrix), len(matrix[0])
        ans = [[0]*n for _ in range(m)]
        value_to_positions = {}
        for i in range(m):
            for j in range(n):
                value_to_positions.setdefault(matrix[i][j], []).append((i, j))
        # Sort unique values
        sorted_values = sorted(value_to_positions.keys())
        # Track the max rank so far for each row and column
        row_max = [0]*m
        col_max = [0]*n

        parent = {}

        def find(x):
            parent.setdefault(x, x)
            if parent[x] != x:
                parent[x] = find(parent[x])
            return parent[x]

        def union(x, y):
            parent[find(x)] = find(y)

        for value in sorted_values:
            parent.clear()
            # Union all positions with the same value in the same row or column
            for i, j in value_to_positions[value]:
                union(('r', i), ('c', j))
            groups = {}
            for i, j in value_to_positions[value]:
                root = find(('r', i))
                groups.setdefault(root, []).append((i, j))
            # For each group, assign the correct rank
            for group in groups.values():
                max_rank = 1
                for i, j in group:
                    max_rank = max(max_rank, row_max[i]+1, col_max[j]+1)
                for i, j in group:
                    ans[i][j] = max_rank
                    row_max[i] = max_rank
                    col_max[j] = max_rank
        return ans
