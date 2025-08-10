#include <algorithm>
#include <climits>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 * int val;
 * TreeNode *left;
 * TreeNode *right;
 * TreeNode() : val(0), left(nullptr), right(nullptr) {}
 * TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        // Initialize max_sum with a very small number to handle negative node values.
        int max_sum = INT_MIN;
        maxGain(root, max_sum);
        return max_sum;
    }

private:
    // Helper function to compute max gain and update the overall max_sum.
    int maxGain(TreeNode* node, int& max_sum) {
        if (!node) {
            return 0;
        }

        // Recursively find the maximum gain from left and right subtrees.
        // We take max with 0 because we don't want to include paths with negative sums.
        int left_gain = std::max(0, maxGain(node->left, max_sum));
        int right_gain = std::max(0, maxGain(node->right, max_sum));

        // Calculate the maximum path sum that includes the current node as the "root" of the path.
        // This path includes the node itself, plus its left and right branches.
        int current_path_sum = node->val + left_gain + right_gain;
        
        // Update the overall maximum path sum found so far.
        max_sum = std::max(max_sum, current_path_sum);

        // Return the maximum gain that can be extended upwards to the parent node.
        // This path cannot include both left and right children, so we take the better one.
        return node->val + std::max(left_gain, right_gain);
    }
};
