/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// Stack: inorder traversal
// 1) Do In-Order Traversal of the given tree and store the result in a temp array.
// 2) Check if the temp array is sorted in ascending order, if it is, then the tree is BST.
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        stack<TreeNode*> st;
        TreeNode * p = root, * pre = NULL;
        while (p || !st.empty()) { // inorder traversal
            while (p) { // left
                st.push(p);
                p = p->left;
            }
            p = st.top(); st.pop(); // mid
            if (pre && p->val <= pre->val) return false; // logic, must be <=
            pre = p;
            p = p->right; // right
        }
        return true;
    }
};