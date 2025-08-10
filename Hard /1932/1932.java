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
import java.util.*;

class Solution {
    public TreeNode canMerge(List<TreeNode> trees) {
        Map<Integer, TreeNode> roots = new HashMap<>();
        Set<Integer> leaves = new HashSet<>();
        for (TreeNode t : trees) {
            roots.put(t.val, t);
            if (t.left != null) leaves.add(t.left.val);
            if (t.right != null) leaves.add(t.right.val);
        }

        // Find the unique root (not a leaf in any other tree)
        TreeNode root = null;
        for (TreeNode t : trees) {
            if (!leaves.contains(t.val)) {
                root = t;
                break;
            }
        }
        if (root == null) return null;

        // Remove the chosen root from roots map
        roots.remove(root.val);

        // Merge trees recursively
        if (!merge(root, roots, Integer.MIN_VALUE, Integer.MAX_VALUE)) return null;
        if (!roots.isEmpty()) return null; // Not all trees merged

        // Check BST validity and uniqueness
        Set<Integer> seen = new HashSet<>();
        if (!isBST(root, seen, Integer.MIN_VALUE, Integer.MAX_VALUE)) return null;
        if (seen.size() != leaves.size() + 1) return null;
        return root;
    }

    // Merge subtrees by replacing leaves with matching roots
    private boolean merge(TreeNode node, Map<Integer, TreeNode> roots, int min, int max) {
        if (node == null) return true;
        if (node.left == null && node.right == null && roots.containsKey(node.val)) {
            TreeNode sub = roots.remove(node.val);
            node.left = sub.left;
            node.right = sub.right;
        }
        if (node.val <= min || node.val >= max) return false;
        return merge(node.left, roots, min, node.val) && merge(node.right, roots, node.val, max);
    }

    // Validate BST and collect all node values
    private boolean isBST(TreeNode node, Set<Integer> seen, int min, int max) {
        if (node == null) return true;
        if (node.val <= min || node.val >= max || !seen.add(node.val)) return false;
        return isBST(node.left, seen, min, node.val) && isBST(node.right, seen, node.val, max);
    }
}
