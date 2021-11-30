/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (!root) return NULL;
        if (root->val > key) {
            root->left = deleteNode(root->left, key);
        }
        else if (root->val < key) {
            root->right = deleteNode(root->right, key);
        }
        else {
            // left/right not exist, root=right/left
            // left & right not exist, root=null
            if (!root->left || !root->right) {
                root = (root->left) ? root->left : root->right;
            }
            else {
                // both left and right exist, root=min of right
                TreeNode * cur = root->right;
                while (cur->left) cur = cur->left;
                root->val =  cur->val;
                root->right = deleteNode(root->right, cur->val);
            }
        }
        return root;
    }
};