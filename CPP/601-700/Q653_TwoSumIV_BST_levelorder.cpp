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
    bool findTarget(TreeNode* root, int k) {
        unordered_set<int> st;
        queue<TreeNode*> q{{root}};
        // level order traversal
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                TreeNode * top = q.front(); q.pop();
                if (st.count(k - top->val)) return true;
                st.insert(top->val);
                if (top->left) q.push(top->left);
                if (top->right) q.push(top->right);
            }
        }
        return false;
    }
};