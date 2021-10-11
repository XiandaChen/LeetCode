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
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if (!root) return {};
        
        vector<int> res;
        
        if (root->left || root->right) res.push_back(root->val); // add root val
        
        // If the root does not have a left child, then the left boundary is empty.
        leftBoundary(root->left, res);
        leaves(root, res);
        rightBoundary(root->right, res);
        
        return res;
    }
    
    void leftBoundary(TreeNode * root, vector<int> & res) {
        if (!root || (!root->left && !root->right)) return; // empty root, or root is a leaf
        res.push_back(root->val);
        if (root->left) leftBoundary(root->left, res);
        else leftBoundary(root->right, res);
    }
    
    void rightBoundary(TreeNode * root, vector<int> & res) {
        if (!root || (!root->left && !root->right)) return; // empty root, or root is a leaf
        if (root->right) rightBoundary(root->right, res);
        else rightBoundary(root->left, res);
        res.push_back(root->val);  // NOTE, ordering
    } 
    
    void leaves(TreeNode * root, vector<int> & res) {
        if (!root) return;
        if (!root->left && !root->right) res.push_back(root->val);
        if (root->left) leaves(root->left, res);
        if (root->right) leaves(root->right, res);
    }
};