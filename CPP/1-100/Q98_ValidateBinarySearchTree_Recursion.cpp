/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // long to cover int edge case: 2147483647
        return isValidBST(root, LONG_MIN, LONG_MAX); 
    }
    bool isValidBST(TreeNode * node, long mn, long mx) {
        if (!node) return true;
        if (node->val <= mn || node->val >= mx) return false;
        return isValidBST(node->left, mn, node->val) 
            && isValidBST(node->right, node->val, mx);
    }
};