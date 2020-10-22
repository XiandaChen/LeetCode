class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // 1,2,7,4,3,1 => 1,3,7,4,2,1 => 1,3,1,2,4,7
        int n = nums.size(), i = n - 2, j = n - 1;
        
        // non-decreasing portion from the end
        while (i >= 0 && nums[i] >= nums[i + 1]) --i; // nums[i] = 2
        
        if (i >= 0) { // check otherwise input nums is largest permutation
            while (j >= 0 && nums[j] <= nums[i]) --j; // nums[j] = 3
            swap(nums[i], nums[j]);
        }
        
        reverse(nums.begin() + i + 1, nums.end());
    }
};