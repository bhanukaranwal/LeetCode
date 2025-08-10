class Solution {
    public int sumOfFlooredPairs(int[] nums) {
        int MOD = 1_000_000_007;
        int max = 0;
        for (int x : nums) max = Math.max(max, x);
        int[] freq = new int[max + 1];
        for (int x : nums) freq[x]++;
        int[] prefix = new int[max + 2];
        for (int i = 1; i <= max; ++i) prefix[i] = prefix[i - 1] + freq[i];
        long res = 0;
        for (int i = 1; i <= max; ++i) {
            if (freq[i] == 0) continue;
            for (int k = 1; i * k <= max; ++k) {
                int l = i * k, r = Math.min(max, i * (k + 1) - 1);
                int count = prefix[r] - prefix[l - 1];
                res = (res + (long)freq[i] * k % MOD * count % MOD) % MOD;
            }
        }
        return (int)res;
    }
}
