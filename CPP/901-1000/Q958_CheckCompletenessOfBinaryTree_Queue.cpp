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
    bool isCompleteTree(TreeNode* root) {
        if (!root) return true;
        queue<TreeNode*> q({root});
        while (!q.empty()) {
            TreeNode * t = q.front(); q.pop();
            if (!t) break;      // stop when meeting null node
            q.push(t->left);
            q.push(t->right);
        }
        while (!q.empty()) { // if non-null node exist
            TreeNode * t = q.front(); q.pop();
            if (t) return false;
        }
        return true;
    }
};