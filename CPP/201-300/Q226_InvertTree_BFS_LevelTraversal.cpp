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
    TreeNode* invertTree(TreeNode* root) {
        if (!root) return NULL;
        queue<TreeNode*> q{{root}};
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop();
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
                TreeNode * tmp = t->left;
                t->left = t->right;
                t->right = tmp;
            }
        }
        return root;
    }
};