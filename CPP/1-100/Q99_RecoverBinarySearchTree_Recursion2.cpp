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
    TreeNode * pre = NULL, * first = NULL, * second = NULL;
    void recoverTree(TreeNode* root) {
        if (!root) return;
        inorderTraversalDFS(root);
        swap(first->val, second->val);
    }
    void inorderTraversalDFS(TreeNode * root) {
        if (!root) return;
        inorderTraversalDFS(root->left);
        if (pre && pre->val > root->val) {
            if(!first) first = pre; // must check if(!first)
            second = root;
        }
        pre = root;
        inorderTraversalDFS(root->right);
    }
};