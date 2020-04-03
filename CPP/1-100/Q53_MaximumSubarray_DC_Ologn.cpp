class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        return helper(nums, 0, nums.size() - 1);
    }
    int helper(vector<int> & nums, int left, int right) {
        if (left >= right) return nums[left]; // must be >=, not ==
        int mid = left + (right - left) / 2;
        int lmax = helper(nums, left, mid - 1);
        int rmax = helper(nums, mid + 1, right);
        // start from nums[mid] to calculate mid-maxSubArray
        int mmax = nums[mid], tmp = mmax;
        // extent midmax-subarray from mid to left
        for (int i = mid - 1; i >= left; --i) { // must be >=, not >
            tmp += nums[i];
            mmax = max(mmax, tmp);
        }
        // extent midmax-subarray from mid to right
        tmp = mmax;
        for (int i = mid + 1; i <= right; ++i) { // must be <=, not <
            tmp += nums[i];
            mmax = max(mmax, tmp);
        }
        return max(mmax, max(lmax, rmax));
    }
};