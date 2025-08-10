import java.util.*;

class Solution {
    private int[] parent;
    private int[] componentSize;

    public int minMalwareSpread(int[][] graph, int[] initial) {
        int n = graph.length;
        parent = new int[n];
        componentSize = new int[n];

        // 1. Initialize DSU
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            componentSize[i] = 1;
        }

        // 2. Mark clean nodes
        boolean[] isClean = new boolean[n];
        Arrays.fill(isClean, true);
        for (int node : initial) isClean[node] = false;

        // 3. Union clean nodes
        for (int i = 0; i < n; ++i) {
            if (!isClean[i]) continue;
            for (int j = i + 1; j < n; ++j) {
                if (isClean[j] && graph[i][j] == 1) {
                    union(i, j);
                }
            }
        }

        // 4. For each initial node, find which components it can infect
        int[] affectedCount = new int[n];
        Map<Integer, Set<Integer>> malwareSources = new HashMap<>();
        for (int node : initial) {
            Set<Integer> affectedComponents = new HashSet<>();
            for (int j = 0; j < n; ++j) {
                if (isClean[j] && graph[node][j] == 1) {
                    affectedComponents.add(find(j));
                }
            }
            for (int root : affectedComponents) {
                affectedCount[root]++;
            }
            malwareSources.put(node, affectedComponents);
        }

        // 5. Choose the node whose removal saves the most nodes
        int maxSaved = -1, result = Arrays.stream(initial).min().getAsInt();
        for (int node : initial) {
            int saved = 0;
            for (int root : malwareSources.get(node)) {
                if (affectedCount[root] == 1) {
                    saved += componentSize[root];
                }
            }
            if (saved > maxSaved || (saved == maxSaved && node < result)) {
                maxSaved = saved;
                result = node;
            }
        }
        return result;
    }

    private int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    private void union(int a, int b) {
        int rootA = find(a), rootB = find(b);
        if (rootA != rootB) {
            parent[rootA] = rootB;
            componentSize[rootB] += componentSize[rootA];
        }
    }
}
