class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        if (!root) return NULL;
        
        if (nodes.size() == 1) return nodes[0];
        
        for (auto & node : nodes) {
            if (node == root) return root;  // if nodes include root
        }
        
        bool left = search(root->left, nodes);
        bool right = search(root->right, nodes);
        
        if (left && right) { // nodes exist in both left and right sides
            return root;
        }
        else if (left) {
            return lowestCommonAncestor(root->left, nodes);
        }
        else {
            return lowestCommonAncestor(root->right, nodes);
        }
    }
    
    // true: if there is a node in current tree
    bool search(TreeNode* root, vector<TreeNode*> &nodes) {
        if (!root) return false;
        for (auto & node : nodes) {
            if (root->val == node->val) return true;
        }
        return search(root->left, nodes) || search(root->right, nodes);
    }
};