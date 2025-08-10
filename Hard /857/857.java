import java.util.*;

class Solution {
    public double mincostToHireWorkers(int[] quality, int[] wage, int k) {
        int n = quality.length;
        // Each worker: [ratio, quality]
        double[][] workers = new double[n][2];
        for (int i = 0; i < n; ++i) {
            workers[i][0] = (double) wage[i] / quality[i];
            workers[i][1] = quality[i];
        }
        // Sort by wage-to-quality ratio ascending
        Arrays.sort(workers, Comparator.comparingDouble(a -> a[0]));
        
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        int sumQ = 0;
        double minCost = Double.MAX_VALUE;
        
        for (int i = 0; i < n; ++i) {
            int q = (int) workers[i][1];
            sumQ += q;
            maxHeap.offer(q);
            if (maxHeap.size() > k) {
                sumQ -= maxHeap.poll();
            }
            if (maxHeap.size() == k) {
                minCost = Math.min(minCost, sumQ * workers[i][0]);
            }
        }
        return minCost;
    }
}
