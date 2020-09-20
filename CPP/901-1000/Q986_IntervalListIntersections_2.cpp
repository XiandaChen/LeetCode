class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> res;
        int n = A.size(), m = B.size(), i = 0, j = 0;
        while (i < n && j < m) {
            if (A[i][1] < B[j][0]) ++i; // no-overlapping, A[i] < B[j]
            else if (B[j][1] < A[i][0]) ++j;
            else {  // overlapping
                res.push_back({{max(A[i][0], B[j][0]), min(A[i][1], B[j][1])}});
                if (A[i][1] < B[j][1]) ++i;
                else ++j;
            }
        }
        return res;
    }
};