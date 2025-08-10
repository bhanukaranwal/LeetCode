class TreeAncestor {
    private static final int LOG = 16; // Since n <= 5*10^4, log2(5*10^4) < 16
    private int[][] up;

    public TreeAncestor(int n, int[] parent) {
        int maxLog = 1;
        while ((1 << maxLog) <= n) maxLog++;
        up = new int[n][maxLog];
        for (int i = 0; i < n; i++) {
            up[i][0] = parent[i];
        }
        for (int j = 1; j < maxLog; j++) {
            for (int i = 0; i < n; i++) {
                int p = up[i][j - 1];
                up[i][j] = (p == -1) ? -1 : up[p][j - 1];
            }
        }
    }

    public int getKthAncestor(int node, int k) {
        int j = 0;
        while (k > 0 && node != -1) {
            if ((k & 1) != 0) node = up[node][j];
            k >>= 1;
            j++;
        }
        return node;
    }
}
