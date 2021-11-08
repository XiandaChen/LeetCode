// 74. Search a 2D Matrix (Binary Search)
// matrix = {{1,3,5,7},
//			{10,11,16,20},
// 			{23,30,34,60}}
// 240. Search a 2D Matrix II 
// matrix = {{1, 2, 3,  11, 15, 16},
//			{4, 6, 10, 12, 17, 20},
//			{5, 13, 18, 19, 22, 23}};
// search from topright: O(M + N) 
// optimize ==> O(M + logN) or O(logM + N)
class Solution {
public:
	bool binarySearch (vector<int> & matrix, int target) {
		int left = 0, right = matrix.size() - 1;
		while (left <= right) {
			int mid = left + (right - left) / 2;

			if (matrix[mid] == target) return true;
			else if (matrix[mid] > target) right = mid - 1;
			else left = mid + 1;
		}

		return false;
	}

	bool searchMatrix (vector<vector<int>> &matrix, int target) {
		if (matrix.empty() || matrix[0].empty()) return false;
		int m = (int)matrix.size(), n = (int)matrix[0].size();
		int i = 0, j = n - 1;

		while (i < m) {
			if (matrix[i][j] == target) return true;
			else if (matrix[i][j] > target) {
				if (binarySearch(matrix[i], target)) return true;
				i++;
			}
			else {
				i++;
			}
		}

		return false;
	}
};














