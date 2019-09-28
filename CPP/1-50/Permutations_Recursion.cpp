class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> out, visited(nums.size(), 0);
        permuteDFS(nums, 0, visited, out, res);
        return res;
    }
    void permuteDFS(vector<int>& nums, int level, vector<int>& visited, vector<int>& out, vector<vector<int>>& res) {
        if (level == nums.size()) {res.push_back(out); return;}
        for (int i = 0; i < nums.size(); i++) {
            if (visited[i]) continue;
            visited[i] = 1;
            out.push_back(nums[i]);
            permuteDFS(nums, level + 1, visited, out, res);
            out.pop_back();
            visited[i] = 0;
        }
    }
};