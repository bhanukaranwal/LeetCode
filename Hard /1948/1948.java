class Solution {
    static class Trie {
        Map<String, Trie> children = new HashMap<>();
        String name;
        boolean deleted = false;
        Trie(String name) { this.name = name; }
    }

    public List<List<String>> deleteDuplicateFolder(List<List<String>> paths) {
        Trie root = new Trie("");
        // Build Trie
        for (List<String> path : paths) {
            Trie node = root;
            for (String folder : path) {
                node = node.children.computeIfAbsent(folder, k -> new Trie(folder));
            }
        }

        // Postorder serialize and mark duplicates
        Map<String, List<Trie>> map = new HashMap<>();
        serialize(root, map);

        // Mark all duplicates for deletion
        for (List<Trie> group : map.values()) {
            if (group.size() > 1) {
                for (Trie node : group) node.deleted = true;
            }
        }

        // Collect all remaining paths
        List<List<String>> res = new ArrayList<>();
        dfs(root, new ArrayList<>(), res);
        return res;
    }

    // Serialize subtree, return serialization string
    private String serialize(Trie node, Map<String, List<Trie>> map) {
        if (node.children.isEmpty()) return "";
        List<String> parts = new ArrayList<>();
        for (String key : new TreeSet<>(node.children.keySet())) {
            Trie child = node.children.get(key);
            String sub = serialize(child, map);
            parts.add("(" + key + sub + ")");
        }
        String serial = String.join("", parts);
        map.computeIfAbsent(serial, k -> new ArrayList<>()).add(node);
        return serial;
    }

    // DFS to collect all non-deleted paths
    private void dfs(Trie node, List<String> path, List<List<String>> res) {
        if (!node.name.equals("") && !node.deleted) {
            res.add(new ArrayList<>(path));
        }
        for (Trie child : node.children.values()) {
            if (!child.deleted) {
                path.add(child.name);
                dfs(child, path, res);
                path.remove(path.size() - 1);
            }
        }
    }
}
