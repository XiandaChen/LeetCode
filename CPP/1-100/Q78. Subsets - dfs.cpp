class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        vector<int> out;
        helper(nums, 0, out, res);
        return res;
    }
    
    void helper(vector<int>& nums, int pos, vector<int> & out, vector<vector<int>> & res) {
        res.push_back(out);
        
        for (int i = pos; i < (int) nums.size(); i++) {
            out.push_back(nums[i]);
            helper(nums, i + 1, out, res);
            out.pop_back();
        }
    }
};