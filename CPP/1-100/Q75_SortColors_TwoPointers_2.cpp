class Solution {
public:
    void sortColors(vector<int>& nums) {
        int left = 0, right = nums.size() - 1, cur = 0;
        while (cur <= right) { // cur, <=
            if (nums[cur] == 0) 
                swap(nums[left++], nums[cur++]);
            else if (nums[cur] == 2)
                swap(nums[right--], nums[cur]); // not cur++
            else
                ++cur;
        }
    }
};