/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
// dp[i][j]: unique BTS's with root between i and j
class Solution {
public:
    vector<TreeNode*> generateTrees(int n) {
        if (n == 0) return {};
        vector<vector<vector<TreeNode*>>> memo(n, vector<vector<TreeNode*>> (n));
        return generateTrees(1, n, memo);
    }
    vector<TreeNode*> generateTrees(int start, int end, vector<vector<vector<TreeNode*>>> & memo) {
        if (start > end) return {nullptr};  // vector {nullptr}
        if (!memo[start - 1][end - 1].empty()) return memo[start - 1][end - 1];
        vector<TreeNode*> res;
        for (int i = start; i <= end; ++i) {
            vector<TreeNode*> left = generateTrees(start, i - 1, memo);   // divide
            vector<TreeNode*> right = generateTrees(i + 1, end, memo);
            for (auto a : left) {   // conque
                for (auto b : right) {
                    TreeNode* node = new TreeNode(i);
                    node->left = a;
                    node->right = b;
                    res.push_back(node);
                }
            }
        }
        return memo[start - 1][end - 1] = res;
    }
};Q95_UniqueBinarySearchTreesII_DC