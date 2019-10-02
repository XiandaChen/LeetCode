class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> out;
        sort(nums.begin(), nums.end());
        subsetsDFS(nums, 0, out, res);
        return res;
    }
    void subsetsDFS(vector<int>& nums, int pos, vector<int>& out, vector<vector<int>>& res) {
        res.push_back(out); // not selecting pos-th num
        for (int i = pos; i < nums.size(); ++i) { // select pos-th num
            out.push_back(nums[i]);
            subsetsDFS(nums, i + 1, out, res);
            out.pop_back();
        }
    }
};