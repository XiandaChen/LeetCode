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
    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> res;
        preorderTraversalDFS(root, res);
        return res;
    }
    void preorderTraversalDFS(TreeNode* root, vector<int>& res) {
        if (!root) return;
        res.push_back(root->val);
        if (root->left) preorderTraversalDFS(root->left, res);
        if (root->right) preorderTraversalDFS(root->right, res);
    }
};