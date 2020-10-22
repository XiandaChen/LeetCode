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
    int maxAncestorDiff(TreeNode* root) {
        if (!root) return 0; // corner case
        int res = INT_MIN;
        stack<pair<TreeNode*, vector<int>>> st; // node-ancestorValues
        st.push({root, vector<int>()});
        while (!st.empty()) { // preorder traversal
            TreeNode * cur = st.top().first;
            vector<int> ancestors = st.top().second;
            st.pop();
            for (int anc : ancestors) {
                res = max(res, abs(cur->val - anc));
            }
            ancestors.push_back(cur->val);
            if (cur->right) st.push({cur->right, ancestors});
            if (cur->left) st.push({cur->left, ancestors});
        }
        return res;
    }
};