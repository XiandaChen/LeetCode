class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        // base case
        if (nums.empty() || nums[0] > target || nums[nums.size() - 1] < target) return {-1, -1};
        vector<int> res(2, -1);
        res[0] = binarySearch(nums, target, false);
        res[1] = binarySearch(nums, target, true);
        return res;
    }
    int binarySearch(vector<int>& nums, int target, bool findLast) {
        int keyIndx = -1, left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] > target) right = mid - 1;
            else if (nums[mid] < target) left = mid + 1;
            else { // (nums[mid] == target)
                keyIndx = mid;
                if (findLast) { // to find the last one
                    left = mid + 1;
                }
                else { // to find the first one
                    right = mid - 1; 
                }
            }
        }
        return keyIndx;
    }
};

