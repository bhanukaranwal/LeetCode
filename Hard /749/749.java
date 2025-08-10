import java.util.*;

class Solution {
    private static final int[] dx = {0, 0, 1, -1};
    private static final int[] dy = {1, -1, 0, 0};

    public int containVirus(int[][] isInfected) {
        int m = isInfected.length, n = isInfected[0].length;
        int result = 0;

        while (true) {
            // Each region: infected cells, threatened cells, wall count
            List<Set<Integer>> regions = new ArrayList<>();
            List<Set<Integer>> threats = new ArrayList<>();
            List<Integer> walls = new ArrayList<>();
            boolean[][] visited = new boolean[m][n];

            // Find all regions
            for (int i = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (isInfected[i][j] == 1 && !visited[i][j]) {
                        Set<Integer> region = new HashSet<>();
                        Set<Integer> threat = new HashSet<>();
                        int[] wall = new int[1];
                        dfs(isInfected, i, j, visited, region, threat, wall, m, n);
                        regions.add(region);
                        threats.add(threat);
                        walls.add(wall[0]);
                    }
                }
            }

            if (regions.isEmpty()) break;

            // Find the region with the largest threat
            int maxThreatIdx = 0;
            for (int i = 1; i < threats.size(); ++i) {
                if (threats.get(i).size() > threats.get(maxThreatIdx).size()) {
                    maxThreatIdx = i;
                }
            }

            // Add walls for the most dangerous region
            result += walls.get(maxThreatIdx);

            // Quarantine the most dangerous region
            for (int idx = 0; idx < regions.size(); ++idx) {
                for (int code : regions.get(idx)) {
                    int x = code / n, y = code % n;
                    if (idx == maxThreatIdx) {
                        isInfected[x][y] = -1; // Quarantined
                    }
                }
            }

            // Spread the virus from other regions
            for (int idx = 0; idx < regions.size(); ++idx) {
                if (idx == maxThreatIdx) continue;
                for (int code : threats.get(idx)) {
                    int x = code / n, y = code % n;
                    if (isInfected[x][y] == 0) {
                        isInfected[x][y] = 1;
                    }
                }
            }

            // If no more threats, break
            boolean hasThreat = false;
            for (Set<Integer> threat : threats) {
                if (!threat.isEmpty()) {
                    hasThreat = true;
                    break;
                }
            }
            if (!hasThreat) break;
        }
        return result;
    }

    private void dfs(int[][] grid, int x, int y, boolean[][] visited,
                     Set<Integer> region, Set<Integer> threat, int[] wall, int m, int n) {
        visited[x][y] = true;
        region.add(x * n + y);
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 0 || ny < 0 || nx >= m || ny >= n) continue;
            if (grid[nx][ny] == 0) {
                wall[0]++;
                threat.add(nx * n + ny);
            } else if (grid[nx][ny] == 1 && !visited[nx][ny]) {
                dfs(grid, nx, ny, visited, region, threat, wall, m, n);
            }
        }
    }
}
