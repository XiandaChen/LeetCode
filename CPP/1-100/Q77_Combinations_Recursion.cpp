class Solution {
public:
    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> res;
        vector<int> out;
        combineDFS(n, k, 1, out, res);
        return res;
    }
    void combineDFS(int n, int k, int level, vector<int>& out, vector<vector<int>>& res) {
        if (out.size() == k) {res.push_back(out); return;}
        for (int i = level; i <= n; i++) {
            out.push_back(i);
            combineDFS(n, k, i + 1, out, res);
            out.pop_back();
        }
    }
};