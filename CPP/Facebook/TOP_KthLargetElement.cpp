class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
	// method 1: sort(): Time O(NlogN), Space O(1); 
	// method 2: priority_queue: Time O(N), Space O(N)
	// method 3: quicksort: Time O(N), Space O(1)
        int left = 0, right = nums.size() - 1;
        while (true) { // left part: larger than pivot
            int pivot = quicksort(nums, left, right);
            if (pivot == k -1) return nums[pivot];
            if (pivot > k - 1) right = pivot - 1;
            else left = pivot + 1;
        }
    }
    int quicksort(vector<int> & nums, int left, int right) { // quick sort partition: decreasing
        int pivot = nums[left], l = left + 1, r = right;
        while (l <= r) {
            if (nums[l] < pivot && nums[r] > pivot) 
                swap(nums[l++], nums[r--]);
            if (nums[l] >= pivot) l++;
            if (nums[r] <= pivot) r--;
        }
        swap(nums[left], nums[r]);
        return r;
    }
};