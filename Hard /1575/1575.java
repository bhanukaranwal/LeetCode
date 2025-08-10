class Solution {
    static final int MOD = 1_000_000_007;
    int[][] memo;
    int[] locations;
    int finish, n;

    public int countRoutes(int[] locations, int start, int finish, int fuel) {
        this.locations = locations;
        this.finish = finish;
        this.n = locations.length;
        this.memo = new int[n][fuel + 1];
        for (int i = 0; i < n; i++) {
            Arrays.fill(memo[i], -1);
        }
        return dfs(start, fuel);
    }

    private int dfs(int pos, int fuel) {
        if (fuel < 0) return 0;
        if (memo[pos][fuel] != -1) return memo[pos][fuel];
        int ans = (pos == finish) ? 1 : 0;
        for (int next = 0; next < n; next++) {
            if (next != pos) {
                int cost = Math.abs(locations[pos] - locations[next]);
                if (fuel >= cost) {
                    ans = (ans + dfs(next, fuel - cost)) % MOD;
                }
            }
        }
        memo[pos][fuel] = ans;
        return ans;
    }
}
