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
    vector<int> postorderTraversal(TreeNode* root) {
        if (!root) return {}; // must to prevent access null pointer at line 19
        vector<int> res;
        stack<TreeNode*> st{{root}};
        TreeNode * pre = root; // pre: node pre-added to res
        while (!st.empty()) {
            TreeNode * t = st.top();
            if ((!t->left && !t->right) || t->left == pre || t->right == pre) {
                res.push_back(t->val);
                st.pop();
                pre = t;
            }
            else {
                if (t->right) st.push(t->right);
                if (t->left) st.push(t->left);
            }
        }
        return res;
    }
};