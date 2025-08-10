class Solution {
    public int maxJumps(int[] arr, int d) {
        int n = arr.length;
        int[] dp = new int[n];
        int res = 1;
        for (int i = 0; i < n; i++) dfs(i, arr, d, dp);
        for (int v : dp) res = Math.max(res, v);
        return res;
    }
    private int dfs(int i, int[] arr, int d, int[] dp) {
        if (dp[i] != 0) return dp[i];
        int n = arr.length, ans = 1;
        for (int dir = -1; dir <= 1; dir += 2) {
            for (int j = i + dir; j >= 0 && j < n && Math.abs(j - i) <= d && arr[j] < arr[i]; j += dir) {
                ans = Math.max(ans, 1 + dfs(j, arr, d, dp));
                if (arr[j] >= arr[i]) break;
            }
        }
        return dp[i] = ans;
    }
}
