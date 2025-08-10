class Solution {
    private int ans = Integer.MAX_VALUE;

    public int tilingRectangle(int n, int m) {
        if (n > m) return tilingRectangle(m, n); // symmetry
        int[] heights = new int[m];
        dfs(n, m, heights, 0);
        return ans;
    }

    private void dfs(int n, int m, int[] heights, int count) {
        if (count >= ans) return;
        // Find the leftmost lowest cell
        int minH = Integer.MAX_VALUE, idx = -1;
        for (int i = 0; i < m; i++) {
            if (heights[i] < minH) {
                minH = heights[i];
                idx = i;
            }
        }
        if (minH == n) {
            ans = Math.min(ans, count);
            return;
        }
        // Try to place the largest possible square at this position
        for (int k = Math.min(m - idx, n - minH); k >= 1; k--) {
            boolean canPlace = true;
            for (int j = idx; j < idx + k; j++) {
                if (heights[j] != minH) {
                    canPlace = false;
                    break;
                }
            }
            if (!canPlace) continue;
            // Place the square
            for (int j = idx; j < idx + k; j++) heights[j] += k;
            dfs(n, m, heights, count + 1);
            for (int j = idx; j < idx + k; j++) heights[j] -= k; // backtrack
        }
    }
}
