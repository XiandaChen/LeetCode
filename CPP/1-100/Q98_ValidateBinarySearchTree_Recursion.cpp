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
        vector<int> res;
        inorderTraversalDFS(root, res);
        for (int i = 0; i < (int)res.size() - 1; ++i)
            if (res[i] >= res[i + 1]) return false;
        return true;
    }
    void inorderTraversalDFS(TreeNode* root, vector<int> & res) {
        if (!root) return;
        if (root->left) inorderTraversalDFS(root->left, res);
        res.push_back(root->val);
        if (root->right) inorderTraversalDFS(root->right, res);
    }
};