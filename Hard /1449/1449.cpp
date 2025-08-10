class Solution {
    public String largestNumber(int[] cost, int target) {
        // dp[i]: max number of digits we can get with total cost i
        int[] dp = new int[target + 1];
        // Initialize to -inf except dp[0]=0
        for (int i = 1; i <= target; i++) dp[i] = Integer.MIN_VALUE;
        dp[0] = 0;

        // For each cost, update dp
        for (int d = 0; d < 9; d++) {
            int c = cost[d];
            for (int t = c; t <= target; t++) {
                if (dp[t - c] != Integer.MIN_VALUE) {
                    dp[t] = Math.max(dp[t], dp[t - c] + 1);
                }
            }
        }

        // If impossible, return "0"
        if (dp[target] < 1) return "0";

        // Reconstruct the largest number
        StringBuilder sb = new StringBuilder();
        int t = target;
        for (int d = 8; d >= 0; d--) { // Try largest digit first
            int c = cost[d];
            while (t >= c && dp[t] == dp[t - c] + 1) {
                sb.append(d + 1);
                t -= c;
            }
        }
        return sb.toString();
    }
}
