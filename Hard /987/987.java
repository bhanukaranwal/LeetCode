import java.util.*;

/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     int val;
 *     TreeNode left;
 *     TreeNode right;
 *     TreeNode() {}
 *     TreeNode(int val) { this.val = val; }
 *     TreeNode(int val, TreeNode left, TreeNode right) {
 *         this.val = val;
 *         this.left = left;
 *         this.right = right;
 *     }
 * }
 */
class Solution {
    private static class Tuple {
        int row, col, val;
        Tuple(int row, int col, int val) {
            this.row = row;
            this.col = col;
            this.val = val;
        }
    }

    public List<List<Integer>> verticalTraversal(TreeNode root) {
        List<Tuple> nodes = new ArrayList<>();
        dfs(root, 0, 0, nodes);

        // Sort by col, then row, then value
        Collections.sort(nodes, (a, b) -> {
            if (a.col != b.col) return a.col - b.col;
            if (a.row != b.row) return a.row - b.row;
            return a.val - b.val;
        });

        List<List<Integer>> res = new ArrayList<>();
        int prevCol = Integer.MIN_VALUE;
        for (Tuple t : nodes) {
            if (t.col != prevCol) {
                res.add(new ArrayList<>());
                prevCol = t.col;
            }
            res.get(res.size() - 1).add(t.val);
        }
        return res;
    }

    private void dfs(TreeNode node, int row, int col, List<Tuple> nodes) {
        if (node == null) return;
        nodes.add(new Tuple(row, col, node.val));
        dfs(node.left, row + 1, col - 1, nodes);
        dfs(node.right, row + 1, col + 1, nodes);
    }
}
