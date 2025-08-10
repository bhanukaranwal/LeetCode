class Solution {
    public int[] findRedundantDirectedConnection(int[][] edges) {
        int n = edges.length;
        int[] parent = new int[n + 1];
        int[] cand1 = null, cand2 = null;
        for (int[] edge : edges) {
            if (parent[edge[1]] == 0) {
                parent[edge[1]] = edge[0];
            } else {
                cand1 = new int[]{parent[edge[1]], edge[1]};
                cand2 = edge;
            }
        }
        for (int i = 0; i <= n; i++) parent[i] = i;
        for (int[] edge : edges) {
            if (cand2 != null && edge == cand2) continue;
            int u = edge[0], v = edge[1];
            int pu = find(parent, u);
            if (pu == v) return cand1 == null ? edge : cand1;
            parent[v] = pu;
        }
        return cand2;
    }
    private int find(int[] parent, int x) {
        if (parent[x] != x) parent[x] = find(parent, parent[x]);
        return parent[x];
    }
}
