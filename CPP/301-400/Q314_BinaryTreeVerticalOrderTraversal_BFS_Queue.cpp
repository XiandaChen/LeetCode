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
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> res;
        // root order: 0; left: -1; right: +1
        map<int, vector<int>> m; // vertical order--nodes
        queue<pair<int, TreeNode*>> q;  // order-node*
        q.push({0, root});
        
        // level order traversal
        while (!q.empty()) {
            auto a = q.front(); q.pop();
            m[a.first].push_back(a.second->val);
            if (a.second->left) q.push({a.first - 1, a.second->left});
            if (a.second->right) q.push({a.first + 1, a.second->right});
        }
        
        for (auto a : m) res.push_back(a.second);
        
        return res;
    }
};