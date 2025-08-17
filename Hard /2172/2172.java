class Solution {
    public int maximumANDSum(int[] nums, int ns) {
        int complete = (int)Math.pow(3, ns) - 1;
        Integer[] dp = new Integer[complete + 1];
        BiFunction<Integer, Integer, Integer>[] dfs = new BiFunction[1];
        dfs[0] = (i, mask) -> {
            if (dp[mask] != null) {
                return dp[mask];
            }
            if (i == nums.length) {
                return 0;
            }
            int res = 0;
            int bit = 1;
            for (int slot = 1; slot <= ns; slot++) {
                if (mask / bit % 3 < 2) {
                    res = Math.max(res, (nums[i] & slot) + dfs[0].apply(i + 1, mask + bit));
                }
                bit *= 3;
            }
            return dp[mask] = res;
        };
        return dfs[0].apply(0, 0);
    }
}
