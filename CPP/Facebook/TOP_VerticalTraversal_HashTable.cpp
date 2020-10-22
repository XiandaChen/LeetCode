class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (!root) return {};
        map<int, vector<pair<int, int>>> m; // x-<y,val>, map: increasing x
        helper(root, 0, 0, m); // get all pairs: <x-<y,val>>
        vector<vector<int>> res;
        auto cmp = [] (pair<int, int>&a, pair<int, int>&b) {
            return a.first > b.first || (a.first == b.first && a.second < b.second); };
        for (auto a : m) {
            vector<int> col;
            sort(a.second.begin(), a.second.end(), cmp);
            for (int i = 0; i < a.second.size(); ++i)
                col.push_back(a.second[i].second);
            res.push_back(col);
        }
        return res;
    }
    void helper(TreeNode* node, int x, int y, map<int, vector<pair<int, int>>>& m) {
        if (!node) return;
        m[x].push_back({y, node->val});
        helper(node->left, x - 1, y - 1, m);
        helper(node->right, x + 1, y - 1, m);
    }
};