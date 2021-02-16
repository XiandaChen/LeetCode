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
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        return buildTree(preorder, 0, preorder.size() - 1, inorder, 0, inorder.size() - 1);
    }
    TreeNode * buildTree(vector<int> &preorder, int preleft, int preright, vector<int> &inorder, int inleft, int inright) {
        if (preleft > preright || inleft > inright) return NULL;
        int i = 0;
        for (i = inleft; i <= inright; ++i) {
            if (preorder[preleft] == inorder[i]) break;
        }
        TreeNode * cur = new TreeNode(preorder[preleft]);
        cur->left = buildTree(preorder, preleft + 1, preleft + i - inleft, inorder, inleft, i - 1);
        cur->right = buildTree(preorder, preleft + i - inleft + 1, preright, inorder, i + 1, inright);
        return cur;
    }
};