class Solution {
    int maxSum = 0;
    public int maxSumBST(TreeNode root) {
        dfs(root);
        return maxSum;
    }
    private int[] dfs(TreeNode node) {
        if (node == null) return new int[]{1, Integer.MAX_VALUE, Integer.MIN_VALUE, 0};
        int[] l = dfs(node.left), r = dfs(node.right);
        if (l[0] == 1 && r[0] == 1 && node.val > l[2] && node.val < r[1]) {
            int sum = l[3] + r[3] + node.val;
            maxSum = Math.max(maxSum, sum);
            return new int[]{1, Math.min(l[1], node.val), Math.max(r[2], node.val), sum};
        }
        return new int[]{0, 0, 0, 0};
    }
}
