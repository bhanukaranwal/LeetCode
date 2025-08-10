class Solution {
    public List<Boolean> areConnected(int n, int threshold, int[][] queries) {
        int[] parent = new int[n + 1];
        for (int i = 1; i <= n; i++) parent[i] = i;

        // Union-Find helpers
        java.util.function.IntUnaryOperator find = new java.util.function.IntUnaryOperator() {
            public int applyAsInt(int x) {
                if (parent[x] != x) parent[x] = applyAsInt(parent[x]);
                return parent[x];
            }
        };
        java.util.function.BiConsumer<Integer, Integer> union = (a, b) -> {
            int pa = find.applyAsInt(a), pb = find.applyAsInt(b);
            if (pa != pb) parent[pa] = pb;
        };

        // Connect all numbers with their multiples for z > threshold
        for (int z = threshold + 1; z <= n; z++) {
            for (int mult = 2 * z; mult <= n; mult += z) {
                union.accept(z, mult);
            }
        }

        // Answer queries
        List<Boolean> res = new ArrayList<>();
        for (int[] q : queries) {
            res.add(find.applyAsInt(q[0]) == find.applyAsInt(q[1]));
        }
        return res;
    }
}
