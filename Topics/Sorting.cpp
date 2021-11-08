// 912. Sort an Array
// Input: nums = [5,1,1,2,0,0]; Output: [0,0,1,1,2,5]
// QuickSort: Time O(NlogN), Space O(NlogN)
// leetcode => Time Limit Exceeded => for nums=[1,2,3,..50000]
class Solution {
public:
    vector<int> sortArray(vector<int> & nums) {
        quickSort(nums, 0, nums.size() - 1);
        return nums;
    }

    void quickSort(vector<int> & nums, int start, int end) {
        if (start >= end) return;
        int pos = partition(nums, start, end);
        quickSort(nums, start, pos - 1);
        quickSort(nums, pos + 1, end);
    }

    int partition(vector<int> & nums, int start, int end) {
        int pivot = nums[start], left = start + 1, right = end;

        while (left <= right) {
            if (nums[left] > pivot && nums[right] < pivot) {
                swap(nums[left++], nums[right--]);
            }
            else if (nums[left] <= pivot) { // duplicates
                left++;
            }
            else if ( nums[right] >= pivot) { // duplicates
                right--;
            }
        }

        swap(nums[start], nums[right]);

        return right;
    }
};
// MergeSort: Time O(NlogN), Space O(N), pass leetcode tests
class Solution {
public:
    vector<int> sortArray(vector<int> & nums) {
        mergeSort(nums, 0, nums.size() - 1);
        return nums;
    }

    void mergeSort(vector<int> & nums, int start, int end) {
        if (start >= end) return;
        int mid = start + (end - start) / 2;
        mergeSort(nums, start, mid);
        mergeSort(nums, mid + 1, end);
        merge(nums, start, mid, end);
    }

    void merge(vector<int> & nums, int start, int mid, int end) {
        vector<int> tmp(end - start + 1);
        int i = start, j = mid + 1, k = 0;
        while (i <= mid && j <= end) {
            if (nums[i] < nums[j]) tmp[k++] = nums[i++];
            else tmp[k++] = nums[j++];
        }
        while (i <= mid) tmp[k++] = nums[i++];
        while (j <= end) tmp[k++] = nums[j++];
        
        for (int idx = 0; idx < tmp.size(); idx++) 
            nums[start + idx] = tmp[idx];
    }
};

// 215. Kth Largest Element in an Array => QuickSort
// Input: [3,2,3,1,2,4,5,5,6] and k = 4; Output: 4
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
	// quick sort partition: decreasing
    int findKthLargest(vector<int> & nums, int left, int right) { 
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





