class Solution {
public:
    int equalToDescendants(TreeNode* root) {
        int res = 0;
        treeSum(root, res);
        return res;
    }
    // sum of the tree rooted at node
    long long treeSum(TreeNode * node, int & res) {
        if (!node) return 0;
        long long lsum = treeSum(node->left, res);
        long long rsum = treeSum(node->right, res);
        if ((lsum + rsum) == node->val) res++;
        return (lsum + rsum + node->val);
    }
};