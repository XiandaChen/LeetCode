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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        vector<vector<int>> res;
        levelOrderBottom(root, 0, res);
        return vector<vector<int>> (res.rbegin(), res.rend());
    }
    void levelOrderBottom(TreeNode * root, int level, vector<vector<int>> & res) {
        if (!root) return;
        if (res.size() == level) res.push_back({});
        res[level].push_back(root->val);
        if (root->left) levelOrderBottom(root->left, level + 1, res);
        if (root->right) levelOrderBottom(root->right, level + 1, res);
    }
};