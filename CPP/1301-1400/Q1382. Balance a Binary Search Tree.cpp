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
    TreeNode* balanceBST(TreeNode* root) {
        vector<TreeNode*> orders;
        inorder(root, orders);
        return buildBST(orders, 0, orders.size() - 1); // build BST using mid node as root
    }
    
    void inorder(TreeNode* root, vector<TreeNode*> & orders) {
        if (!root) return;
        inorder(root->left, orders);
        orders.push_back(root);
        inorder(root->right, orders);
    }
    
    TreeNode * buildBST(vector<TreeNode*> & orders, int start, int end) {
        if (start > end) return NULL; // NOTE, must
        int mid = start + (end - start) / 2;
        
        TreeNode * node = orders[mid];
        node->left = buildBST(orders, start, mid - 1);
        node->right = buildBST(orders, mid + 1, end);
        
        return node;
    }
};