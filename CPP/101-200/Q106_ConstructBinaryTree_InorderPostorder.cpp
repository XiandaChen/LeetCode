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
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return buildTree(inorder, 0, inorder.size() - 1, postorder, 0, postorder.size() - 1);
    }
    TreeNode * buildTree(vector<int> &inorder, int inleft, int inright, vector<int> &postorder, int postleft, int postright) {
        if (inleft > inright || postleft > postright) return NULL;
        int i = 0;
        for (i = inleft; i <= inright; ++i)
            if (postorder[postright] == inorder[i]) break;
        TreeNode * cur = new TreeNode(inorder[i]);
        cur->left = buildTree(inorder, inleft, i - 1, postorder, postleft, postleft + i - inleft - 1);
        cur->right = buildTree(inorder, i + 1, inright, postorder, postleft + i - inleft, postright - 1);
        return cur;
    }
};