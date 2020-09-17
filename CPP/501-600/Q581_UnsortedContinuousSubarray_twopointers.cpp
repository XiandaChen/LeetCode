class Solution {
public:
    int findUnsortedSubarray(vector<int>& nums) {
        int n = nums.size(), left = 0, right = n - 1;
        // find unsorted subarray
        while (left < n - 1 && nums[left] <= nums[left + 1]) ++left; // n - 1, <=
        if (left == n - 1) return 0;
        while (right >= 0 && nums[right] >= nums[right - 1]) --right; // >=
        int minsub = INT_MAX, maxsub = INT_MIN;
        for (int i = left; i <= right; ++i) {
            minsub = min(minsub, nums[i]);
            maxsub = max(maxsub, nums[i]);
        }
        
        // extent unsorted subarray
        while (left > 0 && nums[left - 1] > minsub) --left;
        while (right < n - 1 && nums[right + 1] < maxsub ) ++right;
        
        return right - left + 1;
    }
};