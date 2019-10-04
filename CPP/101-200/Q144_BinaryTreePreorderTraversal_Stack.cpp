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
    vector<int> preorderTraversal(TreeNode* root) {
        if (!root) return{};
        vector<int> res;
        stack<TreeNode*> st{{root}};
        while (!st.empty()) {
            TreeNode * t = st.top();
            st.pop();
            res.push_back(t->val);
            if (t->right) st.push(t->right);
            if (t->left) st.push(t->left);
        }
        return res;
    }
};