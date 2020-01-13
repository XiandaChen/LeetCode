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
    int countNodes(TreeNode* root) {
        int lheight = 0, rheight = 0;
        TreeNode * ltree = root, * rtree = root;
        while (ltree) {
            lheight += 1; ltree = ltree->left;
        }
        while (rtree) {
            rheight += 1; rtree = rtree->right;
        }
        if (lheight == rheight) return pow(2, lheight) - 1;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};