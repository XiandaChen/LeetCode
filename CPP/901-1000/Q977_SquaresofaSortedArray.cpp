class Solution {
public:
    vector<int> sortedSquares(vector<int>& A) {
        int n = A.size(), left = 0, right = n - 1, indx = n - 1;
        vector<int> res(n);
        while (left <= right) { // '<='
            if (A[left] * A[left] >= A[right] * A[right]) {
                res[indx--] = A[left] * A[left];
                ++left;
            }
            else {
                res[indx--] = A[right] * A[right];
                --right;
            }
        }
        return res;
    }
};