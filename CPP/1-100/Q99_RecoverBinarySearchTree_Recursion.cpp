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
    void recoverTree(TreeNode* root) {
        vector<TreeNode*> list; // all nodes
        vector<int> vals;
        inorderTraversalDFS(root, list, vals);
        sort(vals.begin(), vals.end());
        for (int i = 0; i < (int)vals.size(); ++i) 
            list[i]->val = vals[i];
    }
    void inorderTraversalDFS(TreeNode* root, vector<TreeNode*> & list, vector<int> & vals) {
        if (!root) return;
        if (root->left) inorderTraversalDFS(root->left, list, vals);
        list.push_back(root);
        vals.push_back(root->val);
        if (root->right) inorderTraversalDFS(root->right, list, vals);
    }
};