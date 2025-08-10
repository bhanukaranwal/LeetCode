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
    public TreeNode recoverFromPreorder(String traversal) {
        Deque<TreeNode> stack = new ArrayDeque<>();
        int i = 0, n = traversal.length();
        while (i < n) {
            int depth = 0;
            // Count dashes to get depth
            while (i < n && traversal.charAt(i) == '-') {
                depth++;
                i++;
            }
            // Parse the number
            int val = 0;
            while (i < n && Character.isDigit(traversal.charAt(i))) {
                val = val * 10 + (traversal.charAt(i) - '0');
                i++;
            }
            TreeNode node = new TreeNode(val);
            // If stack size > depth, pop to the correct parent
            while (stack.size() > depth) stack.pop();
            // Attach to parent
            if (!stack.isEmpty()) {
                if (stack.peek().left == null) stack.peek().left = node;
                else stack.peek().right = node;
            }
            stack.push(node);
        }
        // The bottom of the stack is the root
        while (stack.size() > 1) stack.pop();
        return stack.peek();
    }
}
