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
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (!root) return {};
        map<int, vector<pair<int, int>>> m; // x-[<y, val>..]
        dfs(root, 0, 0, m); // node map
        vector<vector<int>> res;
        for (auto a : m) {
            vector<int> col;
            sort(a.second.begin(), a.second.end()); // sort vector using y's
            for (int i = 0; i < a.second.size(); ++i)
                col.push_back(a.second[i].second);
            res.push_back(col);
        }
        return res;
    }
    void dfs(TreeNode * node, int x, int y, map<int, vector<pair<int, int>>> & m) {
        if (!node) return;
        // by default, sort() in increasing order, need to use "-y" to sort decreasing
        m[x].push_back(make_pair(-y, node->val)); 
        dfs(node->left, x - 1, y - 1, m);
        dfs(node->right, x + 1, y - 1, m);
    }
};