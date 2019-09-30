class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        return maxSubArray_DC(nums, 0, (int)nums.size() - 1);
    }
    int maxSubArray_DC(vector<int>& nums, int left, int right) {
		//only check (left == right) results in runtime error 
        if (left >= right) return nums[left];
        int mid = left + (right - left) / 2;
        int leftmax = maxSubArray_DC(nums, left, mid - 1);
        int rightmax = maxSubArray_DC(nums, mid + 1, right);
        int midmax = nums[mid], tmp = midmax;
        for (int i = mid - 1; i >= left; i--) {
            tmp += nums[i];
            midmax = max(midmax, tmp);
        }
        tmp = midmax;
        for (int i = mid + 1; i <= right; i++) {
            tmp += nums[i];
            midmax = max(midmax, tmp);
        }
        return max(midmax, max(leftmax, rightmax));
    }
};