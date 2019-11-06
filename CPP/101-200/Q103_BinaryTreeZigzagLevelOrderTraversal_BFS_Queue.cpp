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
        if (!root) return {};
        vector<vector<int>> res;
        queue<TreeNode*> q({root});
        int level = 0;
        while (!q.empty()) {
            vector<int> onelevel;
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop();
                onelevel.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            if (level % 2 == 1) reverse(onelevel.begin(), onelevel.end());
            res.push_back(onelevel);
            ++level;
        }
        return res;
    }
};