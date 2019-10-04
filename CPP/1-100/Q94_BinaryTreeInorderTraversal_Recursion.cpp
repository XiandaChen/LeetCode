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
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> res;
        inorderTraversalDFS(root, res);
        return res;
    }
    void inorderTraversalDFS(TreeNode* root, vector<int>& res) {
        if (!root) return;
        if (root->left) inorderTraversalDFS(root->left, res);
        res.push_back(root->val);
        if (root->right) inorderTraversalDFS(root->right, res);
    }
};