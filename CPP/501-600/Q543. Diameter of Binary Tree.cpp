class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        getHeight(root, res);
        return res;  // diameter: in terms of path's length 
    }
    // height: in terms of num of nodes
    int getHeight(TreeNode * node, int & res) { 
        if (!node) return 0;
        int leftHeight = getHeight(node->left, res);
        int rightHeight = getHeight(node->right, res);
        // update global tree diameter
        res = max(res, leftHeight + rightHeight);
        // height of cur node
        return 1 + max(leftHeight, rightHeight);
    }
};