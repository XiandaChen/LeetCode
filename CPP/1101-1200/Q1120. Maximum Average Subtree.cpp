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
    double maximumAverageSubtree(TreeNode* root) {
        int nodeNum = 0, nodeVal = 0;
        double res = 0;
        helper(root, nodeNum, nodeVal, res);
        return res;
    }
    void helper(TreeNode * cur, int & nodeNum, int & nodeVal, double & maxAvg) {
        if (!cur) return ;
        if (!cur->left && !cur->right) { // left node, break recursion
            nodeNum = 1;
            nodeVal = cur->val;
            maxAvg = max(maxAvg, nodeVal * 1.0 / nodeNum);
            return ;
        }
        
        int lnum = 0, lval = 0, rnum = 0, rval = 0; // NOTE, initiaze =0
        helper(cur->left, lnum, lval, maxAvg);
        helper(cur->right, rnum, rval, maxAvg);
        nodeNum = lnum + rnum + 1;
        nodeVal = lval + rval + cur->val;
        maxAvg = max(maxAvg, nodeVal * 1.0 / nodeNum);
    }
};