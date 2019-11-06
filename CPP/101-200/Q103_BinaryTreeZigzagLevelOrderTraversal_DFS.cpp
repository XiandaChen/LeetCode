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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> res;
        levelOrder(root, 0, res);   // start with level=0
        for (int i = res.size() - 1; i >= 0; --i)
            if (i % 2 == 1) reverse(res[i].begin(), res[i].end()); // reverse level%2==1
        return res;
    }
    void levelOrder(TreeNode * root, int level, vector<vector<int>> & res) {
        if (!root) return;
        if (res.size() == level) res.push_back({}); // vector for new level
        res[level].push_back(root->val);
        if (root->left) levelOrder(root->left, level + 1, res);
        if (root->right) levelOrder(root->right, level + 1, res);
    }
};