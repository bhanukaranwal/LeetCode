import java.util.*;

class Solution {
    public int[] sortItems(int n, int m, int[] group, List<List<Integer>> beforeItems) {
        // 1. Assign unique group ids to items with group -1
        int groupId = m;
        for (int i = 0; i < n; i++) {
            if (group[i] == -1) group[i] = groupId++;
        }

        // 2. Build graphs: item-graph and group-graph
        List<List<Integer>> itemGraph = new ArrayList<>();
        int[] itemIndegree = new int[n];
        List<List<Integer>> groupGraph = new ArrayList<>();
        int[] groupIndegree = new int[groupId];
        for (int i = 0; i < n; i++) {
            itemGraph.add(new ArrayList<>());
        }
        for (int i = 0; i < groupId; i++) {
            groupGraph.add(new ArrayList<>());
        }

        for (int i = 0; i < n; i++) {
            for (int prev : beforeItems.get(i)) {
                itemGraph.get(prev).add(i);
                itemIndegree[i]++;
                if (group[i] != group[prev]) {
                    groupGraph.get(group[prev]).add(group[i]);
                    groupIndegree[group[i]]++;
                }
            }
        }

        // 3. Topological sort for groups
        List<Integer> groupOrder = topoSort(groupGraph, groupIndegree, groupId);
        if (groupOrder.isEmpty()) return new int[0];

        // 4. Topological sort for items
        List<Integer> itemOrder = topoSort(itemGraph, itemIndegree, n);
        if (itemOrder.isEmpty()) return new int[0];

        // 5. Group items by group id in sorted order
        Map<Integer, List<Integer>> groupToItems = new HashMap<>();
        for (int item : itemOrder) {
            groupToItems.computeIfAbsent(group[item], k -> new ArrayList<>()).add(item);
        }

        // 6. Build result by group order
        List<Integer> res = new ArrayList<>();
        for (int gid : groupOrder) {
            List<Integer> items = groupToItems.getOrDefault(gid, new ArrayList<>());
            res.addAll(items);
        }

        // Convert to array
        return res.stream().mapToInt(i -> i).toArray();
    }

    // Standard Kahn's algorithm for topological sort
    private List<Integer> topoSort(List<List<Integer>> graph, int[] indegree, int n) {
        List<Integer> order = new ArrayList<>();
        Queue<Integer> q = new ArrayDeque<>();
        for (int i = 0; i < n; i++) {
            if (indegree[i] == 0) q.offer(i);
        }
        while (!q.isEmpty()) {
            int u = q.poll();
            order.add(u);
            for (int v : graph.get(u)) {
                if (--indegree[v] == 0) q.offer(v);
            }
        }
        return order.size() == n ? order : new ArrayList<>();
    }
}
