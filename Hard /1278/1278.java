class Solution {
    public int palindromePartition(String s, int k) {
        int n = s.length();
        // minChange[i][j]: min number of changes to make s[i..j] a palindrome
        int[][] minChange = new int[n][n];
        for (int len = 2; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                minChange[i][j] = minChange[i + 1][j - 1];
                if (s.charAt(i) != s.charAt(j)) minChange[i][j]++;
            }
        }

        // dp[i][kk]: min changes to split s[0..i] into kk palindromes
        int[][] dp = new int[n][k + 1];
        for (int[] row : dp) java.util.Arrays.fill(row, Integer.MAX_VALUE / 2);

        // Base case: 1 partition
        for (int i = 0; i < n; i++) {
            dp[i][1] = minChange[0][i];
        }

        for (int i = 0; i < n; i++) {
            for (int kk = 2; kk <= Math.min(k, i + 1); kk++) {
                for (int j = kk - 2; j < i; j++) {
                    dp[i][kk] = Math.min(dp[i][kk], dp[j][kk - 1] + minChange[j + 1][i]);
                }
            }
        }
        return dp[n - 1][k];
    }
}
