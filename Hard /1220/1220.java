class Solution {
    public int countVowelPermutation(int n) {
        final int MOD = 1_000_000_007;
        // Indices: 0-a, 1-e, 2-i, 3-o, 4-u
        long[] dp = new long[5];
        Arrays.fill(dp, 1); // Base case: for n=1, each vowel is a valid string

        for (int k = 2; k <= n; k++) {
            long[] next = new long[5];
            // 'a' can only follow 'e', 'i', 'u'
            next[0] = (dp[1] + dp[2] + dp[4]) % MOD;
            // 'e' can only follow 'a', 'i'
            next[1] = (dp[0] + dp[2]) % MOD;
            // 'i' can only follow 'e', 'o'
            next[2] = (dp[1] + dp[3]) % MOD;
            // 'o' can only follow 'i'
            next[3] = dp[2] % MOD;
            // 'u' can only follow 'i', 'o'
            next[4] = (dp[2] + dp[3]) % MOD;
            dp = next;
        }
        long res = 0;
        for (long v : dp) res = (res + v) % MOD;
        return (int) res;
    }
}
