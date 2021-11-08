#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
// #include <st>

using namespace std;

int partition(vector<int> & nums, int start, int end);
void quickSort(vector<int> & nums, int start, int end);


void desendSort(vector<int> &nums) {
    quickSort(nums, 0, nums.size() - 1);
}

void quickSort(vector<int> & nums, int start, int end) {
    if (start < end) {
        int pos = partition(nums, start, end);

        quickSort(nums, start, pos - 1);
        quickSort(nums, pos + 1, end);
    }

}

// nums are unique
int partition(vector<int> & nums, int start, int end) {
    // pivot 
    // partiton array into two part, left part > pivot, right < pivot
    int pivot = nums[start], left = start + 1, right = end;

    while (left <= right) {
        if (nums[left] < pivot && nums[right] > pivot) {
            swap(nums[left++], nums[right--]);
        }
        else if (nums[left] > pivot) {
            left++;
        }
        else if ( nums[right] < pivot) {
            right--;
        }
    }

    swap(nums[start], nums[right]);

    return right;
}

int main() {

    vector<int> nums = {1, 3, 7, 2};

    cout << "before sorting: ";
    for (int num : nums) cout << num;

    desendSort(nums);

    cout << "\n after sorting: ";
    for (int num : nums) cout << num;


    return 0;
}
