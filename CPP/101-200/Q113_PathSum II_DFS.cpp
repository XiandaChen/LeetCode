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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (!root) return {};
        vector<vector<int>> res;
        vector<int> out;
        dfs(root, sum, out, res);
        return res;
    }
    void dfs(TreeNode * node, int sum, vector<int> & out, vector<vector<int>> & res) {
        if (!node) return;
        out.push_back(node->val); // must
        if (!node->left && !node->right && node->val == sum)
            res.push_back(out);
        if (node->left)
            dfs(node->left, sum - node->val, out, res);
        if (node->right)
            dfs(node->right, sum - node->val, out, res);
        out.pop_back(); // must
    }
};