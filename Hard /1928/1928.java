import java.util.*;

class Solution {
    public int minCost(int maxTime, int[][] edges, int[] passingFees) {
        int n = passingFees.length;
        List<int[]>[] graph = new List[n];
        for (int i = 0; i < n; ++i) graph[i] = new ArrayList<>();
        for (int[] e : edges) {
            graph[e[0]].add(new int[]{e[1], e[2]});
            graph[e[1]].add(new int[]{e[0], e[2]});
        }
        // cost[city][time] = min cost to reach city at time
        int[][] cost = new int[n][maxTime + 1];
        for (int[] row : cost) Arrays.fill(row, Integer.MAX_VALUE);
        cost[0][0] = passingFees[0];

        PriorityQueue<int[]> pq = new PriorityQueue<>(Comparator.comparingInt(a -> a[0]));
        pq.offer(new int[]{passingFees[0], 0, 0}); // {cost, time, city}

        while (!pq.isEmpty()) {
            int[] cur = pq.poll();
            int c = cur[0], t = cur[1], u = cur[2];
            if (u == n - 1) return c;
            if (cost[u][t] < c) continue; // Already found a better way
            for (int[] nei : graph[u]) {
                int v = nei[0], time = nei[1];
                int newTime = t + time;
                if (newTime > maxTime) continue;
                int newCost = c + passingFees[v];
                if (cost[v][newTime] > newCost) {
                    cost[v][newTime] = newCost;
                    pq.offer(new int[]{newCost, newTime, v});
                }
            }
        }
        return -1;
    }
}
