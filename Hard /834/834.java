import java.util.*;

class Solution {
    public int[] sumOfDistancesInTree(int n, int[][] edges) {
        List<List<Integer>> tree = new ArrayList<>();
        for (int i = 0; i < n; ++i) tree.add(new ArrayList<>());
        for (int[] e : edges) {
            tree.get(e[0]).add(e[1]);
            tree.get(e[1]).add(e[0]);
        }
        int[] res = new int[n];
        int[] count = new int[n]; // count[i]: size of subtree rooted at i
        dfs(0, -1, tree, res, count); // post-order
        dfs2(0, -1, tree, res, count, n); // pre-order
        return res;
    }

    // Post-order: fill res[0] and count[]
    private void dfs(int node, int parent, List<List<Integer>> tree, int[] res, int[] count) {
        count[node] = 1;
        for (int child : tree.get(node)) {
            if (child == parent) continue;
            dfs(child, node, tree, res, count);
            count[node] += count[child];
            res[node] += res[child] + count[child];
        }
    }

    // Pre-order: fill res[child] using res[parent]
    private void dfs2(int node, int parent, List<List<Integer>> tree, int[] res, int[] count, int n) {
        for (int child : tree.get(node)) {
            if (child == parent) continue;
            // When moving root from node to child:
            // res[child] = res[node] - count[child] + (n - count[child])
            res[child] = res[node] - count[child] + (n - count[child]);
            dfs2(child, node, tree, res, count, n);
        }
    }
}
