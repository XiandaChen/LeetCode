/*
Given a sorted array in which all elements appear twice (one after one) and one element appears only once. 
Find that element in O(log n) complexity.
Input:   arr[] = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8}
Output:  4
*/

/*
All elements before the required have first occurrence at even index (0, 2, ..) and next occurrence at odd index (1, 3, …). 

And all elements after the required element have first occurrence at odd index and next occurrence at even index.

1) Find the middle index, say 'mid'.
2) If 'mid' is even, then compare arr[mid] and arr[mid + 1]. If both are same, then the required element after 'mid' else before 'mid'.
3) If 'mid' is odd, then compare arr[mid] and arr[mid – 1]. If both are same, then the required element after 'mid' else before 'mid'.
*/

int uniqueNum (vector<int> & nums) {
	if (nums.size() == 0) return -1;
	
    int n = nums.size(), left = 0, right = n - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;
        
        // If mid is even and element next to mid is 
        // same as mid, then output element lies on 
        // right side, else on left side 
        if (mid % 2 == 0) {
            if (mid + 1 < n && nums[mid] ==  nums[mid + 1])
                left = mid + 2;
            else
                right = mid - 2;
        }
        else {
            if (mid - 1 >= 0 && nums[mid] == nums[mid - 1])
                left = mid + 1;
            else
                right = mid - 1;
        }
    }
    return nums[right];
}

/*
test:

int main () {
	vector<int> A  = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8};
	vector<int> B = {1, 3, 3, 4, 4, 5, 5, 7, 7, 8, 8};
	vector<int> C  = {1, 1, 3, 3, 4, 4, 5, 5, 7, 7, 8};
	cout << "A: " << uniqueNum(A) << endl;
	cout << "B: " << uniqueNum(B) << endl;
	cout << "C: " << uniqueNum(C) << endl;
	return 0;
}
*/