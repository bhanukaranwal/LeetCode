class Solution {
    public int cutOffTree(List<List<Integer>> forest) {
        int m = forest.size(), n = forest.get(0).size();
        List<int[]> trees = new ArrayList<>();
        for (int i = 0; i < m; i++)
            for (int j = 0; j < n; j++)
                if (forest.get(i).get(j) > 1)
                    trees.add(new int[]{forest.get(i).get(j), i, j});
        Collections.sort(trees, Comparator.comparingInt(a -> a[0]));
        int res = 0, sx = 0, sy = 0;
        for (int[] tree : trees) {
            int d = bfs(forest, sx, sy, tree[1], tree[2]);
            if (d == -1) return -1;
            res += d;
            sx = tree[1];
            sy = tree[2];
        }
        return res;
    }
    private int bfs(List<List<Integer>> forest, int sx, int sy, int tx, int ty) {
        if (sx == tx && sy == ty) return 0;
        int m = forest.size(), n = forest.get(0).size();
        boolean[][] vis = new boolean[m][n];
        Queue<int[]> q = new LinkedList<>();
        q.offer(new int[]{sx, sy, 0});
        vis[sx][sy] = true;
        int[] dirs = {0,1,0,-1,0};
        while (!q.isEmpty()) {
            int[] cur = q.poll();
            for (int d = 0; d < 4; d++) {
                int nx = cur[0] + dirs[d], ny = cur[1] + dirs[d+1];
                if (nx >= 0 && nx < m && ny >= 0 && ny < n && !vis[nx][ny] && forest.get(nx).get(ny) > 0) {
                    if (nx == tx && ny == ty) return cur[2] + 1;
                    vis[nx][ny] = true;
                    q.offer(new int[]{nx, ny, cur[2] + 1});
                }
            }
        }
        return -1;
    }
}
