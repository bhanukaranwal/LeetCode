class Solution {
    public int countPalindromicSubsequences(String s) {
        int n = s.length(), MOD = 1_000_000_007;
        int[][] dp = new int[n][n];
        // next/prev occurrence of each char
        int[][] next = new int[n][4], prev = new int[n][4];
        int[] pos = new int[4];
        Arrays.fill(pos, -1);
        for (int i = 0; i < n; i++) {
            for (int c = 0; c < 4; c++) prev[i][c] = pos[c];
            pos[s.charAt(i) - 'a'] = i;
        }
        Arrays.fill(pos, n);
        for (int i = n - 1; i >= 0; i--) {
            for (int c = 0; c < 4; c++) next[i][c] = pos[c];
            pos[s.charAt(i) - 'a'] = i;
        }
        for (int i = 0; i < n; i++) dp[i][i] = 1;
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                if (s.charAt(i) == s.charAt(j)) {
                    int c = s.charAt(i) - 'a';
                    int ni = next[i][c], pj = prev[j][c];
                    if (ni > pj) {
                        dp[i][j] = (2 * dp[i + 1][j - 1] + 2) % MOD;
                    } else if (ni == pj) {
                        dp[i][j] = (2 * dp[i + 1][j - 1] + 1) % MOD;
                    } else {
                        dp[i][j] = ((2 * dp[i + 1][j - 1] - dp[ni + 1][pj - 1]) % MOD + MOD) % MOD;
                    }
                } else {
                    dp[i][j] = ((dp[i + 1][j] + dp[i][j - 1]) % MOD - dp[i + 1][j - 1] + MOD) % MOD;
                }
            }
        }
        return dp[0][n - 1];
    }
}
