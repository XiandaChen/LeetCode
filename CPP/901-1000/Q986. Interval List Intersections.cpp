class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        int m = A.size(), n = B.size(), i = 0, j = 0;
        vector<vector<int>> res;
        while (i < m && j < n) {
            if (A[i][1] < B[j][0]) ++i;
            else if (B[j][1] < A[i][0]) ++j;
            else {
                int c1 = max(A[i][0], B[j][0]), c2 = min(A[i][1], B[j][1]);
                res.push_back({c1, c2});
                if (A[i][1] < B[j][1]) ++i;  //[1]
                else ++j;
            }
        }
        return res;
    }
};