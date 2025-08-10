class Solution {
    public int minimumDistance(String word) {
        int[][] pos = new int[26][2];
        for (int i = 0, x = 0, y = 0; i < 26; i++) {
            pos[i][0] = x;
            pos[i][1] = y;
            y++;
            if ((i + 1) % 6 == 0) {
                x++;
                y = 0;
            }
        }
        int n = word.length();
        int[][][] dp = new int[n + 1][27][27];
        for (int i = 0; i <= n; i++)
            for (int j = 0; j < 27; j++)
                for (int k = 0; k < 27; k++)
                    dp[i][j][k] = 100000;
        dp[0][26][26] = 0;
        for (int i = 0; i < n; i++) {
            int cur = word.charAt(i) - 'A';
            for (int f1 = 0; f1 < 27; f1++) {
                for (int f2 = 0; f2 < 27; f2++) {
                    int d1 = f1 == 26 ? 0 : Math.abs(pos[cur][0] - pos[f1][0]) + Math.abs(pos[cur][1] - pos[f1][1]);
                    int d2 = f2 == 26 ? 0 : Math.abs(pos[cur][0] - pos[f2][0]) + Math.abs(pos[cur][1] - pos[f2][1]);
                    dp[i + 1][cur][f2] = Math.min(dp[i + 1][cur][f2], dp[i][f1][f2] + d1);
                    dp[i + 1][f1][cur] = Math.min(dp[i + 1][f1][cur], dp[i][f1][f2] + d2);
                }
            }
        }
        int res = 100000;
        for (int f1 = 0; f1 < 27; f1++)
            for (int f2 = 0; f2 < 27; f2++)
                res = Math.min(res, dp[n][f1][f2]);
        return res;
    }
}
