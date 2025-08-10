class Solution {
    public int numberOfArrays(String s, int k) {
        int n = s.length(), mod = 1000000007;
        int[] dp = new int[n + 1];
        dp[n] = 1; // base case: empty string
        for (int i = n - 1; i >= 0; i--) {
            if (s.charAt(i) == '0') continue; // no leading zeros
            long num = 0;
            for (int j = i; j < n; j++) {
                num = num * 10 + (s.charAt(j) - '0');
                if (num > k) break;
                dp[i] = (dp[i] + dp[j + 1]) % mod;
            }
        }
        return dp[0];
    }
}
