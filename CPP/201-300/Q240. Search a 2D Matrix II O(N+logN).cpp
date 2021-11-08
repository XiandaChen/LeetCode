class Solution {  // Time optimize ==> O(M + logN) or O(logM + N)
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