/*
Given an array of integers. All numbers occur twice except one number which occurs once. Find this unique number.
Time: O(n), Space: O(1)
Input:  ar[] = {7, 3, 5, 4, 5, 3, 4}
Output: 7 
*/

/*
a) XOR of a number with itself is 0.
b) XOR of a number with 0 is number itself.
*/

int uniqueNum (vector<int> & nums) {
	if (nums.size() == 0) return -1;
	
	// Do XOR of all elements
	// return the single occurrence
	int res = nums[0];
	for (int i = 1; i < nums.size(); ++i)
		res ^= nums[i];
	return res;
}

/*
test:

int main () {
	vector<int> A  = {7, 3, 5, 4, 5, 3, 4};
	vector<int> B = {0, 1, 1, 2, 2, 3, 3};
	vector<int> C  = {5, 5, 4, 4, 3, 3, 2, 2, 1};
	cout << "A: " << uniqueNum(A) << endl;
	cout << "B: " << uniqueNum(B) << endl;
	cout << "C: " << uniqueNum(C) << endl;
	return 0;
}

*/