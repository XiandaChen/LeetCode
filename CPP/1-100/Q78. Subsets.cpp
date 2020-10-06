class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res;
        res.push_back(vector<int>()); // initial with empty subset
        for (auto num : nums) {
            int n = res.size();
            for (int i = 0; i < n; ++i) {
                // create newset from existing one, and add cur num
                vector<int> newset(res[i]);
                newset.push_back(num);
                res.push_back(newset);
            }
        }
        return res;
    }
};