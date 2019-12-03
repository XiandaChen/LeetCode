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
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        return generateTrees(1, n);
    }
    vector<TreeNode*> generateTrees(int start, int end) {
        if (start > end) return {nullptr};  // vector {nullptr}
        vector<TreeNode*> res;
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> left = generateTrees(start, i - 1);   // divide
            vector<TreeNode*> right = generateTrees(i + 1, end);
            for (auto a : left) {   // conque
                for (auto b : right) {
                    TreeNode* node = new TreeNode(i);
                    node->left = a;
                    node->right = b;
                    res.push_back(node);
                }
            }
        }
        return res;
    }
};