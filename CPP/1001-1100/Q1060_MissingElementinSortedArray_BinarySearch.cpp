class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        int cnt = missingCount(nums, right);
        // k-th missing num is not within nums[0] and nums[right]
        if (k > cnt) return nums[right] + k - cnt; 
        // the index of the leftmost lower-bound of K
        while (left < right) {
            int mid = left + (right - left) / 2;
            cnt = missingCount(nums, mid);
            if (k > cnt) left = mid + 1;
            else right = mid;
        }
        // the number of missing at index - 1 must less then K
        return nums[left - 1] + k - missingCount(nums, left - 1);
    }
    int missingCount(vector<int> & nums, int indx) {
        return nums[indx] - nums[0] - indx;
    }
};