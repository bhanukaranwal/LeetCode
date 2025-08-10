class Solution {
    public int numOfWays(int n) {
        int mod = 1000000007;
        long a = 6, b = 6;
        for (int i = 2; i <= n; i++) {
            long na = (3 * a + 2 * b) % mod;
            long nb = (2 * a + 2 * b) % mod;
            a = na;
            b = nb;
        }
        return (int)((a + b) % mod);
    }
}
