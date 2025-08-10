class Solution {
    static final int MAX_BIT = 18; // since val <= 2*10^5

    static class TrieNode {
        TrieNode[] next = new TrieNode[2];
        int count = 0;
    }

    public int[] maxGeneticDifference(int[] parents, int[][] queries) {
        int n = parents.length;
        List<Integer>[] tree = new ArrayList[n];
        for (int i = 0; i < n; ++i) tree[i] = new ArrayList<>();
        int root = -1;
        for (int i = 0; i < n; ++i) {
            if (parents[i] == -1) root = i;
            else tree[parents[i]].add(i);
        }

        // Group queries by node
        Map<Integer, List<int[]>> queryMap = new HashMap<>();
        for (int i = 0; i < queries.length; ++i) {
            int node = queries[i][0], val = queries[i][1];
            queryMap.computeIfAbsent(node, k -> new ArrayList<>()).add(new int[]{val, i});
        }

        int[] ans = new int[queries.length];
        TrieNode trie = new TrieNode();

        dfs(root, tree, queryMap, trie, ans);
        return ans;
    }

    private void dfs(int node, List<Integer>[] tree, Map<Integer, List<int[]>> queryMap, TrieNode trie, int[] ans) {
        insert(trie, node, 1);
        if (queryMap.containsKey(node)) {
            for (int[] q : queryMap.get(node)) {
                ans[q[1]] = query(trie, q[0]);
            }
        }
        for (int child : tree[node]) {
            dfs(child, tree, queryMap, trie, ans);
        }
        insert(trie, node, -1); // remove node value when backtracking
    }

    private void insert(TrieNode root, int num, int delta) {
        TrieNode node = root;
        for (int i = MAX_BIT; i >= 0; --i) {
            int b = (num >> i) & 1;
            if (node.next[b] == null) node.next[b] = new TrieNode();
            node = node.next[b];
            node.count += delta;
        }
    }

    private int query(TrieNode root, int num) {
        TrieNode node = root;
        int res = 0;
        for (int i = MAX_BIT; i >= 0; --i) {
            int b = (num >> i) & 1;
            int toggled = b ^ 1;
            if (node.next[toggled] != null && node.next[toggled].count > 0) {
                res |= (1 << i);
                node = node.next[toggled];
            } else {
                node = node.next[b];
            }
        }
        return res;
    }
}
