class Solution {
public:
    int sumNumbers(TreeNode* root) {
        return helper(root, 0);
    }
    int helper(TreeNode * node, int pathsum) { // not & pathsum
        if (!node) return 0;
        pathsum = pathsum * 10 + node->val;
        if (!node->left && !node->right) return pathsum;
        return helper(node->left, pathsum) + helper(node->right, pathsum);
    }
};