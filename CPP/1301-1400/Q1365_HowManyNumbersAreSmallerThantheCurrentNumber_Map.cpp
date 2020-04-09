class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        map<int, int> m;
        for (int num : nums) ++m[num];
        vector<int> res(nums.size());
        for (int i = 0; i < nums.size(); ++i) {
            for (auto a : m) {
                if (a.first < nums[i]) 
                    res[i] += a.second;
            }
        }
        return res;
    }
};