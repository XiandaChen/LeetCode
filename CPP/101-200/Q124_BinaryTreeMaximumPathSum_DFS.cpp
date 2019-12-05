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
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        DFS(root, res);
        return res;
    }
    int DFS(TreeNode * node, int & res) { // maxsum of path from cur node to a leaf 
        if (!node) return 0;
        int left = max(DFS(node->left, res), 0); // maxPathSum of path rooting a node->left
        int right = max(DFS(node->right, res), 0);
        res = max(res, left + right + node->val);
        return max(left, right) + node->val; // only max(left, right)
    }
};