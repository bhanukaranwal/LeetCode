class Solution {
    public int minFallingPathSum(int[][] grid) {
        int n = grid.length;
        int[] prev = new int[n];
        // Initialize with the first row
        for (int j = 0; j < n; j++) prev[j] = grid[0][j];

        for (int i = 1; i < n; i++) {
            int min1 = Integer.MAX_VALUE, min2 = Integer.MAX_VALUE, idx1 = -1;
            // Find the smallest and second smallest in prev
            for (int j = 0; j < n; j++) {
                if (prev[j] < min1) {
                    min2 = min1;
                    min1 = prev[j];
                    idx1 = j;
                } else if (prev[j] < min2) {
                    min2 = prev[j];
                }
            }
            int[] curr = new int[n];
            for (int j = 0; j < n; j++) {
                // If same column as min1, use min2; else use min1
                curr[j] = grid[i][j] + (j == idx1 ? min2 : min1);
            }
            prev = curr;
        }
        // The answer is the minimum in the last row
        int res = Integer.MAX_VALUE;
        for (int x : prev) res = Math.min(res, x);
        return res;
    }
}
