class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) { // Divide and Conquer
            int pos = findKthLargest(nums, left, right);
            if (pos == k - 1) return nums[pos];
            else if (pos > k - 1) right = pos - 1;
            else left = pos + 1;
        }
    }
    int findKthLargest(vector<int> & nums, int left, int right) { // quick sort partition: decreasing
        int pivot = nums[left], l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot)
                swap(nums[l++], nums[r--]);
            if (nums[l] >= pivot) l++;	// decreasing
            if (nums[r] <= pivot) r--;	// decreasing
        }
        swap(nums[left], nums[r]);
        return r;
    }
};