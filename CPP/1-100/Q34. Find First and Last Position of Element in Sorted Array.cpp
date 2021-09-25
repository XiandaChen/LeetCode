class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int n = nums.size(), left = 0, right = n - 1;
        int resLeft = -1, resRight = -1;
        
        // first num equal to target
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) left = mid + 1;
            else right = mid - 1;
        }
        if (left >= n || nums[left] != target) return {-1, -1};
        
        resLeft = left;
        
        // smallest num larger than target
        left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) left = mid + 1;
            else right = mid - 1;
        }
        resRight = left - 1;
        
        return {resLeft, resRight};
    }
};