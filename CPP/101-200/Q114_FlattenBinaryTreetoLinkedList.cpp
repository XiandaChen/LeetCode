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
    void flatten(TreeNode* root) {
        TreeNode * cur = root;
        while (cur) {
            if (cur->left) {
                TreeNode * tmp = cur->left;
                while (tmp->right)
                    tmp = tmp->right;
                tmp->right = cur->right;
                cur->right = cur->left;
                cur->left = NULL; // must include
            }
            cur = cur->right;
        }
    }
};