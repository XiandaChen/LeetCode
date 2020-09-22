class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> res;
        int i = 0, n = nums.size();
        while (i < n) { // cyclic sort
            if (nums[i] != nums[nums[i] - 1])
                swap(nums[i], nums[nums[i] - 1]);
            else {
                ++i;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1)
                res.push_back(nums[i]);
        }
        return res;
    }
};