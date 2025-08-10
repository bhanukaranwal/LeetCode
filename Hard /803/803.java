class Solution {
    int m, n;
    int[][] dirs = {{1,0},{-1,0},{0,1},{0,-1}};
    
    public int[] hitBricks(int[][] grid, int[][] hits) {
        m = grid.length;
        n = grid[0].length;
        int len = hits.length;
        int[] res = new int[len];
        
        // Step 1: Mark all bricks to be hit as 2 (temporarily removed)
        for (int[] hit : hits) {
            int x = hit[0], y = hit[1];
            if (grid[x][y] == 1) grid[x][y] = 2;
        }
        
        // Step 2: Union all stable bricks (after all hits)
        DSU dsu = new DSU(m * n + 1); // extra node for the "roof"
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 1) {
                    if (i == 0) dsu.union(node(i, j), roof());
                    for (int[] d : dirs) {
                        int ni = i + d[0], nj = j + d[1];
                        if (inGrid(ni, nj) && grid[ni][nj] == 1) {
                            dsu.union(node(i, j), node(ni, nj));
                        }
                    }
                }
            }
        }
        
        // Step 3: Process hits in reverse
        for (int k = len - 1; k >= 0; --k) {
            int x = hits[k][0], y = hits[k][1];
            if (grid[x][y] != 2) {
                res[k] = 0;
                continue;
            }
            grid[x][y] = 1; // restore the brick
            int prev = dsu.size(roof());
            // Connect to neighbors if they are bricks
            if (x == 0) dsu.union(node(x, y), roof());
            for (int[] d : dirs) {
                int ni = x + d[0], nj = y + d[1];
                if (inGrid(ni, nj) && grid[ni][nj] == 1) {
                    dsu.union(node(x, y), node(ni, nj));
                }
            }
            int now = dsu.size(roof());
            res[k] = Math.max(0, now - prev - 1); // exclude the brick just restored
        }
        return res;
    }
    
    private int node(int i, int j) {
        return i * n + j;
    }
    private int roof() {
        return m * n;
    }
    private boolean inGrid(int i, int j) {
        return i >= 0 && i < m && j >= 0 && j < n;
    }
    
    // Union-Find with size tracking
    class DSU {
        int[] parent, sz;
        public DSU(int N) {
            parent = new int[N];
            sz = new int[N];
            for (int i = 0; i < N; ++i) {
                parent[i] = i;
                sz[i] = 1;
            }
        }
        public int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        public void union(int x, int y) {
            int xr = find(x), yr = find(y);
            if (xr == yr) return;
            parent[xr] = yr;
            sz[yr] += sz[xr];
        }
        public int size(int x) {
            return sz[find(x)];
        }
    }
}
