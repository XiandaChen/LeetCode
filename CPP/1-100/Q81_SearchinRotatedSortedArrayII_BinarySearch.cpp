// nums may contain duplicates
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target) return true;
            
            if (nums[mid] < nums[right]) { // right part is sorted
                if (nums[mid] < target && target <= nums[right]) left = mid + 1;
                else right = mid - 1;
            }
            else if (nums[mid] > nums[right]) { // left part is sorted
                if (nums[left] <= target && target < nums[mid]) right = mid - 1;
                else left = mid + 1;
            }
            else { // duplicates, nums[mid]==nums[right], [3 1 1] and [1 1 3 1]
                --right;
            }
        }
        return false;
    }
};