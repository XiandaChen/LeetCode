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
    int pathSum(TreeNode* root, int sum) {
        int res = 0;
        vector<TreeNode*> out;
        pathSum(root, sum, 0, out, res);
        return res;
    }
    void pathSum(TreeNode * node, int sum, int curSum, vector<TreeNode*> & out, int & res) {
        if (!node) return;
        curSum += node->val;
        if (curSum == sum) ++res; // path sum equals to given sum
        int tmp = curSum;
        for (int i = 0; i < out.size(); ++i) { // if remove node from the start of the path
            tmp -= out[i]->val;
            if (tmp == sum) ++res;
        }
        out.push_back(node);
        pathSum(node->left, sum, curSum, out, res); // DFS
        pathSum(node->right, sum, curSum, out, res);
        out.pop_back();
    }
};