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
    int rob(TreeNode* root) {
        unordered_map<TreeNode*, int> m;
        return rob(root, m);
    }
    int rob(TreeNode * root, unordered_map<TreeNode*, int> & m) {
        if (!root) return 0;
        if (m.count(root)) return m[root];
        int val = 0;
        if (root->left)
            val += rob(root->left->left, m) + rob(root->left->right, m);
        if (root->right)
            val += rob(root->right->left, m) + rob(root->right->right, m);
        return m[root] = max(root->val + val, rob(root->left, m) + rob(root->right, m));
    }
};