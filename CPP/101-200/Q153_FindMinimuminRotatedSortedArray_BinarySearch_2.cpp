class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = nums.size(), left = 0, right = n - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if ((left < mid) && (nums[mid - 1] > nums[mid])) return nums[mid];
            if ((mid < right) && (nums[mid] > nums[mid + 1])) return nums[mid + 1];
            
            if (nums[left] <= nums[mid]) { // left part is sorted
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        
        return nums[0]; // nums is not rotated
    }
};