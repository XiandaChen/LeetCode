class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int i = 0, n = nums.size();
        while (i < n) {
            if (nums[i] < n && nums[i] != nums[nums[i]])
                swap(nums[i], nums[nums[i]]);
            else ++i;
        }
        for (int i = 0; i < n; ++i) 
            if (nums[i] != i)
                return i;
        return nums.size();
    }
};