class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size(), left = 0, right = n - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // before the single elem,  
            // for each pair, the first elem is at even idx
            if (mid % 2 == 0) {
                if (mid + 1 < n && nums[mid] == nums[mid + 1])
                    left = mid + 2; // NOTE, + 2
                else 
                    right = mid;  // NOTE, not -2
            }
            else {
                if (mid - 1 >= 0 && nums[mid - 1] == nums[mid])
                    left = mid + 1;
                else
                    right = mid;  // NOTE, not -1
            }
        }
        
        return nums[right];
    }
};
