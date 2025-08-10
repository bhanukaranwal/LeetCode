class Solution {
    static final int MOD = 1_000_000_007;

    public int distinctSubseqII(String s) {
        int n = s.length();
        int[] dp = new int[n + 1]; // dp[i]: # of distinct subsequences using first i chars
        dp[0] = 1; // empty subsequence

        int[] last = new int[26]; // last occurrence position + 1 for each char

        for (int i = 1; i <= n; ++i) {
            int c = s.charAt(i - 1) - 'a';
            dp[i] = (2 * dp[i - 1]) % MOD;
            if (last[c] > 0) {
                dp[i] = (dp[i] - dp[last[c] - 1] + MOD) % MOD;
            }
            last[c] = i;
        }
        // Subtract 1 to exclude the empty subsequence
        return (dp[n] - 1 + MOD) % MOD;
    }
}
