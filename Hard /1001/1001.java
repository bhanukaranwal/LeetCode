import java.util.*;

class Solution {
    public int[] gridIllumination(int n, int[][] lamps, int[][] queries) {
        Map<Integer, Integer> row = new HashMap<>();
        Map<Integer, Integer> col = new HashMap<>();
        Map<Integer, Integer> diag = new HashMap<>();
        Map<Integer, Integer> antiDiag = new HashMap<>();
        Set<Long> lampSet = new HashSet<>();

        // Turn on all lamps and update counters
        for (int[] lamp : lamps) {
            int x = lamp[0], y = lamp[1];
            long key = encode(x, y);
            if (lampSet.contains(key)) continue;
            lampSet.add(key);
            row.put(x, row.getOrDefault(x, 0) + 1);
            col.put(y, col.getOrDefault(y, 0) + 1);
            diag.put(x - y, diag.getOrDefault(x - y, 0) + 1);
            antiDiag.put(x + y, antiDiag.getOrDefault(x + y, 0) + 1);
        }

        int[] res = new int[queries.length];
        int[][] dirs = {{0,0},{0,1},{0,-1},{1,0},{1,1},{1,-1},{-1,0},{-1,1},{-1,-1}};

        for (int i = 0; i < queries.length; i++) {
            int x = queries[i][0], y = queries[i][1];
            // Check if illuminated
            if (row.getOrDefault(x, 0) > 0 ||
                col.getOrDefault(y, 0) > 0 ||
                diag.getOrDefault(x - y, 0) > 0 ||
                antiDiag.getOrDefault(x + y, 0) > 0) {
                res[i] = 1;
            } else {
                res[i] = 0;
            }
            // Turn off lamp at (x, y) and its 8 neighbors
            for (int[] d : dirs) {
                int nx = x + d[0], ny = y + d[1];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                long key = encode(nx, ny);
                if (lampSet.remove(key)) {
                    row.put(nx, row.get(nx) - 1);
                    if (row.get(nx) == 0) row.remove(nx);
                    col.put(ny, col.get(ny) - 1);
                    if (col.get(ny) == 0) col.remove(ny);
                    diag.put(nx - ny, diag.get(nx - ny) - 1);
                    if (diag.get(nx - ny) == 0) diag.remove(nx - ny);
                    antiDiag.put(nx + ny, antiDiag.get(nx + ny) - 1);
                    if (antiDiag.get(nx + ny) == 0) antiDiag.remove(nx + ny);
                }
            }
        }
        return res;
    }

    // Helper function must be outside the main method in Java
    private long encode(int x, int y) {
        return ((long)x << 32) | (y & 0xffffffffL);
    }
}
