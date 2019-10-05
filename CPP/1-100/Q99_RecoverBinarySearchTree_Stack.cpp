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
    void recoverTree(TreeNode* root) {
        TreeNode *p = root, * pre = NULL, * first = NULL, * second = NULL;
        stack<TreeNode*> st;
        while (p || !st.empty()) {
            while (p) {
                st.push(p);
                p = p->left;
            }
            p = st.top(); st.pop();
            if (pre && pre->val > p->val) {
                if (!first) first = pre;
                second = p;
            }
            pre = p;
            p = p->right;
        }
        swap(first->val, second->val);
    }
};