class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = firstGreaterEqualto(nums, target);
        // check if leftindx is within the array bounds and target is in the array
        if (left == nums.size() || nums[left] != target) return {-1, -1};
        return {left, firstGreaterEqualto(nums, target + 1) - 1};
    }
    int firstGreaterEqualto(vector<int>& nums, int target) {
        int left = 0, right = nums.size();
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        return right;
    }
};