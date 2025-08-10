import java.util.*;

class Solution {
    public int jobScheduling(int[] startTime, int[] endTime, int[] profit) {
        int n = startTime.length;
        // Step 1: Combine jobs and sort by end time
        int[][] jobs = new int[n][3];
        for (int i = 0; i < n; i++) {
            jobs[i][0] = startTime[i];
            jobs[i][1] = endTime[i];
            jobs[i][2] = profit[i];
        }
        Arrays.sort(jobs, Comparator.comparingInt(a -> a[1]));

        // Step 2: DP array, dp[i] = max profit for first i jobs
        int[] dp = new int[n];
        dp[0] = jobs[0][2];

        for (int i = 1; i < n; i++) {
            int currProfit = jobs[i][2];
            // Binary search for the last job that doesn't overlap
            int l = 0, r = i - 1;
            while (l <= r) {
                int m = l + (r - l) / 2;
                if (jobs[m][1] <= jobs[i][0]) l = m + 1;
                else r = m - 1;
            }
            // r is the index of the last non-overlapping job
            if (r >= 0) currProfit += dp[r];
            dp[i] = Math.max(dp[i - 1], currProfit);
        }
        return dp[n - 1];
    }
}
