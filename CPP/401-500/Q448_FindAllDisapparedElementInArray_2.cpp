class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> res;
        int n = nums.size(), i = 0;
        while (i < n) {
            if (nums[i] - 1 < n && nums[i] != nums[nums[i] - 1]) //
                swap(nums[i], nums[nums[i] - 1]);
            else ++i;
        }
        
        for (int i = 0; i < n; ++i) {
            if (nums[i] != i + 1)
                res.push_back(i+1);
        }
        return res;
    }
};