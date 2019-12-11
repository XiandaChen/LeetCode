class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int i = 0, j = 0; i < nums.size(); ++i) {
            // pointer i for iterating the array, 
            // pointer j just works on non-zero elements
            if (nums[i]) swap(nums[i], nums[j++]);
        }
    }
};