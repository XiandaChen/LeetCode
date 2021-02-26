class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        // flip the image along the diagonal ((x0, yn), (xn,y0))
        int n = matrix.size();
        for (int i = 0; i < n - 1; ++i) {
            for (int j = 0; j < n - i; ++j) {
                swap(matrix[i][j], matrix[n - 1 - j][n - 1 - i]);
            }
        }
        // flip over the middle line at row
        reverse(matrix.begin(), matrix.end());
    }
};