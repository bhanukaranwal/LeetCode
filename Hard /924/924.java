import java.util.*;

class Solution {
    public int minMalwareSpread(int[][] graph, int[] initial) {
        int n = graph.length;
        DSU dsu = new DSU(n);
        // Union all connected nodes
        for (int i = 0; i < n; ++i)
            for (int j = i + 1; j < n; ++j)
                if (graph[i][j] == 1)
                    dsu.union(i, j);

        // Count size of each component
        int[] size = new int[n];
        for (int i = 0; i < n; ++i)
            size[dsu.find(i)]++;

        // Count number of malware in each component
        int[] malwareCount = new int[n];
        for (int node : initial)
            malwareCount[dsu.find(node)]++;

        // Sort initial to ensure smallest index in case of tie
        Arrays.sort(initial);
        int result = initial[0], maxSaved = -1;
        for (int node : initial) {
            int root = dsu.find(node);
            // If this component has exactly one malware, removing it will save the entire component
            if (malwareCount[root] == 1) {
                if (size[root] > maxSaved) {
                    maxSaved = size[root];
                    result = node;
                }
            }
        }
        return result;
    }

    class DSU {
        int[] parent;
        DSU(int n) {
            parent = new int[n];
            for (int i = 0; i < n; ++i) parent[i] = i;
        }
        int find(int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        }
        void union(int x, int y) {
            parent[find(x)] = find(y);
        }
    }
}
