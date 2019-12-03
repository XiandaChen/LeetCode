class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        if (matrix.empty() || matrix[0].empty()) return false; // must check  matrix[0].empty()
        int m = matrix.size(), n = matrix[0].size(), x = m - 1, y = 0;
        while (true) { // binary search from the left-bottom coner
            if (matrix[x][y] == target) return true;
            else if (matrix[x][y] > target) --x;
            else ++y;
            if (x < 0 || y >= n) return false;
        }
        return false;
    }
};