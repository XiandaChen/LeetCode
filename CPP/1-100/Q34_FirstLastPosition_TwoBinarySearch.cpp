class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.empty()) return {-1, -1};
        vector<int> res (2, -1);
        int left = 0, right = nums.size();
        // find the leftmost index
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        // check if leftindx is within the array bounds and target is in the array
        if (right == nums.size() || nums[right] != target) return res;
        res[0] = right;
        left = 0, right = nums.size();
        // find the rightmost index
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) left = mid + 1;
            else right = mid;
        }
        res[1] = right - 1;
        return res;
    }
};