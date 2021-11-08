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


