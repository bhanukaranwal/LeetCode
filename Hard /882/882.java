import java.util.*;

class Solution {
    public int reachableNodes(int[][] edges, int maxMoves, int n) {
        // Build the graph: graph[u] = {v, cnt}
        Map<Integer, Map<Integer, Integer>> graph = new HashMap<>();
        for (int[] e : edges) {
            graph.computeIfAbsent(e[0], x -> new HashMap<>()).put(e[1], e[2]);
            graph.computeIfAbsent(e[1], x -> new HashMap<>()).put(e[0], e[2]);
        }
        // Dijkstra: max moves left to reach each node
        int[] movesLeft = new int[n];
        Arrays.fill(movesLeft, -1);
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> b[1] - a[1]); // [node, movesLeft], max heap
        pq.offer(new int[]{0, maxMoves});
        movesLeft[0] = maxMoves;
        while (!pq.isEmpty()) {
            int[] curr = pq.poll();
            int u = curr[0], moves = curr[1];
            if (moves < movesLeft[u]) continue; // Already found better
            if (!graph.containsKey(u)) continue;
            for (int v : graph.get(u).keySet()) {
                int cost = graph.get(u).get(v) + 1;
                int nextMoves = moves - cost;
                if (nextMoves > movesLeft[v]) {
                    movesLeft[v] = nextMoves;
                    pq.offer(new int[]{v, nextMoves});
                }
            }
        }
        // Count all reachable original nodes
        int result = 0;
        for (int m : movesLeft) if (m >= 0) result++;
        // Count reachable subdivided nodes on each edge
        for (int[] e : edges) {
            int u = e[0], v = e[1], cnt = e[2];
            int a = Math.max(0, movesLeft[u]);
            int b = Math.max(0, movesLeft[v]);
            result += Math.min(cnt, a + b);
        }
        return result;
    }
}
