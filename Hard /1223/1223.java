class Solution {
    public int dieSimulator(int n, int[] rollMax) {
        int MOD = 1_000_000_007;
        // dp[i][j][k]: # of sequences of length i, ending with face j, with k consecutive j's
        int[][][] dp = new int[n + 1][6][16]; // max rollMax[i] is 15
        // Base case: for length 1, each face appears once
        for (int j = 0; j < 6; j++) dp[1][j][1] = 1;

        for (int i = 2; i <= n; i++) {
            for (int j = 0; j < 6; j++) { // current face
                for (int k = 1; k <= rollMax[j]; k++) {
                    if (k == 1) {
                        // Previous face must be different
                        for (int p = 0; p < 6; p++) {
                            if (p == j) continue;
                            for (int t = 1; t <= rollMax[p]; t++) {
                                dp[i][j][1] = (dp[i][j][1] + dp[i-1][p][t]) % MOD;
                            }
                        }
                    } else {
                        // Previous face is same, so k > 1
                        dp[i][j][k] = (dp[i][j][k] + dp[i-1][j][k-1]) % MOD;
                    }
                }
            }
        }

        // Sum all valid sequences of length n
        int res = 0;
        for (int j = 0; j < 6; j++) {
            for (int k = 1; k <= rollMax[j]; k++) {
                res = (res + dp[n][j][k]) % MOD;
            }
        }
        return res;
    }
}
