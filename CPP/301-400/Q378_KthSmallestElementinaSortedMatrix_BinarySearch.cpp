class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int left = matrix[0][0], right = matrix.back().back();
        while (left < right) {
            int mid = left + (right - left) / 2, cnt = 0;
            for (int i = 0; i < matrix.size(); ++i)
                // since end of row-(i-1) may not be less than start of row-i
                // num of elements less than mid in each row
                cnt += upper_bound(matrix[i].begin(), matrix[i].end(), mid) - matrix[i].begin();
            if (cnt < k) left = mid + 1;
            else right = mid;
        }
        return left;
    }
};