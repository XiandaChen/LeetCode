class Solution {
public:
    int findDuplicate(vector<int>& nums) {
            sort(nums.begin(), nums.end());

            int n = nums.size(), left = 0, right = n - 1;
            while (left < right) {
                int mid = left + (right - left) / 2;
                if ((0 < mid && nums[mid - 1] == nums[mid])
                   || (mid < n - 1 && nums[mid + 1] == nums[mid])) return nums[mid];

                if (mid >= nums[mid]) right = mid - 1;
                else left = mid + 1;
            }

            return nums[right];
    }
};