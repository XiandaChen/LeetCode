class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        
        return helper(root, LONG_MAX, LONG_MIN);
    }
    
    bool helper(TreeNode * root, long maxPath, long minPath) {
        if (!root) return true;

        if (root->val <= minPath || root->val >= maxPath) return false;  // NOTE, <=
                
        return helper(root->left, root->val, minPath)
            && helper(root->right, maxPath, root->val);

     }
};
