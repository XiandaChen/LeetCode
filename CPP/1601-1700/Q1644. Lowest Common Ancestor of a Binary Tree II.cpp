// /**
//  * Definition for a binary tree node.
//  * struct TreeNode {
//  *     int val;
//  *     TreeNode *left;
//  *     TreeNode *right;
//  *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
//  * };
//  */
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (checkIfExists(root, p) && checkIfExists(root, q))
            return lca(root, p, q);
        else
            return NULL;
    }
    
    TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root; // one of p/q to be ancestor of the other
        
        TreeNode * left = lca(root->left, p, q);
        TreeNode * right = lca(root->right, p, q);
        
        // if p and q exist at two diff sides, root is the ancestor
        if (left && right) return root;
        
        return (left) ? left : right;
    }
    
    bool checkIfExists(TreeNode* root, TreeNode* node){
        if(root == NULL || node == NULL)
            return false;
        if(root->val == node->val)
            return true;
        if(checkIfExists(root->left, node) || checkIfExists(root->right, node))
            return true;
        
        return false;
    }
};
