class Solution {
    public int minTaps(int n, int[] ranges) {
        int[] maxReach = new int[n + 1];
        for (int i = 0; i <= n; i++) {
            int l = Math.max(0, i - ranges[i]);
            int r = Math.min(n, i + ranges[i]);
            maxReach[l] = Math.max(maxReach[l], r);
        }
        int taps = 0, end = 0, far = 0;
        for (int i = 0; i <= n; i++) {
            if (i > far) return -1;
            far = Math.max(far, maxReach[i]);
            if (i == end) {
                if (end == n) break;
                taps++;
                end = far;
            }
        }
        return taps;
    }
}
