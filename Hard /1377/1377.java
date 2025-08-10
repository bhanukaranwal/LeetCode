import java.util.*;

class Solution {
    public double frogPosition(int n, int[][] edges, int t, int target) {
        List<Integer>[] g = new List[n + 1];
        for (int i = 1; i <= n; i++) g[i] = new ArrayList<>();
        for (int[] e : edges) {
            g[e[0]].add(e[1]);
            g[e[1]].add(e[0]);
        }
        boolean[] visited = new boolean[n + 1];
        return dfs(1, t, target, g, visited);
    }
    private double dfs(int node, int t, int target, List<Integer>[] g, boolean[] visited) {
        visited[node] = true;
        if (t == 0 || (g[node].size() == 1 && node != 1)) return node == target ? 1.0 : 0.0;
        int cnt = 0;
        for (int nei : g[node]) if (!visited[nei]) cnt++;
        if (cnt == 0) return node == target ? 1.0 : 0.0;
        double res = 0.0;
        for (int nei : g[node]) {
            if (!visited[nei]) res += dfs(nei, t - 1, target, g, visited);
        }
        return res / cnt;
    }
}
