import java.util.*;

class Solution {
    public int maxPerformance(int n, int[] speed, int[] efficiency, int k) {
        int mod = 1000000007;
        int[][] engs = new int[n][2];
        for (int i = 0; i < n; i++) {
            engs[i][0] = efficiency[i];
            engs[i][1] = speed[i];
        }
        Arrays.sort(engs, (a, b) -> b[0] - a[0]);
        PriorityQueue<Integer> heap = new PriorityQueue<>();
        long sum = 0, res = 0;
        for (int[] e : engs) {
            heap.offer(e[1]);
            sum += e[1];
            if (heap.size() > k) sum -= heap.poll();
            res = Math.max(res, sum * e[0]);
        }
        return (int)(res % mod);
    }
}
