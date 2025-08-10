class Solution {
    static final int MOD = 1_000_000_007;
    long[] fact, invFact;
    List<Integer>[] tree;

    public int waysToBuildRooms(int[] prevRoom) {
        int n = prevRoom.length;
        fact = new long[n+1];
        invFact = new long[n+1];
        buildFactorials(n);

        tree = new List[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        for (int i = 1; i < n; ++i) {
            tree[prevRoom[i]].add(i);
        }

        return (int) dfs(0)[1];
    }

    // Returns [size, ways] for subtree rooted at node
    private long[] dfs(int node) {
        long ways = 1;
        int size = 0;
        for (int child : tree[node]) {
            long[] res = dfs(child);
            ways = ways * res[1] % MOD * comb(size + (int)res[0], (int)res[0]) % MOD;
            size += res[0];
        }
        return new long[]{size + 1, ways};
    }

    // n choose k modulo MOD
    private long comb(int n, int k) {
        return fact[n] * invFact[k] % MOD * invFact[n - k] % MOD;
    }

    private void buildFactorials(int n) {
        fact[0] = invFact[0] = 1;
        for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % MOD;
        invFact[n] = pow(fact[n], MOD - 2);
        for (int i = n - 1; i >= 1; --i) invFact[i] = invFact[i + 1] * (i + 1) % MOD;
    }

    private long pow(long x, int y) {
        long res = 1;
        while (y > 0) {
            if ((y & 1) == 1) res = res * x % MOD;
            x = x * x % MOD;
            y >>= 1;
        }
        return res;
    }
}
