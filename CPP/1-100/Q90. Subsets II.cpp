class Solution {
public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        vector<vector<int>> res(1); // initial with one empty subset
        sort(nums.begin(), nums.end()); // sort, so duplicates are aligned together
        int endIdx = 0;
        for (int i = 0; i < (int)nums.size(); ++i) {
            int startIdx = 0; // subwindow of res to add new num
            if (i > 0 && nums[i] == nums[i - 1]) // if duplicate
                startIdx = endIdx;
            endIdx = res.size();
            for (int j = startIdx; j < endIdx; ++j) { // <
                vector<int> newset(res[j]);
                newset.push_back(nums[i]);
                res.push_back(newset);
            }
        }
        return res;
    }
};
