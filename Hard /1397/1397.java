class Solution {
    int mod = 1000000007;
    int[][][] memo;
    int[] fail;
    String evil, s1, s2;
    int n, m;
    public int findGoodStrings(int n, String s1, String s2, String evil) {
        this.n = n;
        this.evil = evil;
        this.s1 = s1;
        this.s2 = s2;
        this.m = evil.length();
        this.memo = new int[n + 1][m + 1][4];
        this.fail = new int[m];
        for (int[][] a : memo) for (int[] b : a) java.util.Arrays.fill(b, -1);
        for (int i = 1, j = 0; i < m; i++) {
            while (j > 0 && evil.charAt(i) != evil.charAt(j)) j = fail[j - 1];
            if (evil.charAt(i) == evil.charAt(j)) fail[i] = ++j;
        }
        return dp(0, 0, 3);
    }
    int dp(int i, int match, int bound) {
        if (match == m) return 0;
        if (i == n) return 1;
        if (memo[i][match][bound] != -1) return memo[i][match][bound];
        char from = (bound & 1) > 0 ? s1.charAt(i) : 'a';
        char to = (bound & 2) > 0 ? s2.charAt(i) : 'z';
        int res = 0;
        for (char c = from; c <= to; c++) {
            int k = match;
            while (k > 0 && evil.charAt(k) != c) k = fail[k - 1];
            if (evil.charAt(k) == c) k++;
            int nb = 0;
            if ((bound & 1) > 0 && c == from) nb |= 1;
            if ((bound & 2) > 0 && c == to) nb |= 2;
            res = (res + dp(i + 1, k, nb)) % mod;
        }
        return memo[i][match][bound] = res;
    }
}
