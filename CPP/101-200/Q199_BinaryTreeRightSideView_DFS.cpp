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
    vector<int> rightSideView(TreeNode* root) {
        vector<int> res;
        vector<vector<int>> out;
        levelOrder(root, 0, out);
        for (auto t : out)
            res.push_back(t.back());
        return res;
    }
    void levelOrder(TreeNode * root, int level, vector<vector<int>> & out) {
        if (!root) return;
        if (out.size() == level) out.push_back({});
        out[level].push_back(root->val);
        if(root->left) levelOrder(root->left, level + 1, out);
        if(root->right) levelOrder(root->right, level + 1, out);
    }
};