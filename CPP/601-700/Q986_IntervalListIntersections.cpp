class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> res;
        int m = A.size(), n = B.size(), ai = 0, bi = 0;
        while (ai < m && bi < n) {
            int aj = A[ai].size() - 1, bj = B[bi].size() - 1;
            if (A[ai][aj] < B[bi][0]) {
                ++ai;
            }
            else if (B[bi][bj] < A[ai][0]) {
                ++bi;
            }
            else {
                int c1 = max(A[ai][0], B[bi][0]), c2 = min(A[ai][aj], B[bi][bj]);
                res.push_back({{c1, c2}});
                if (A[ai][aj] < B[bi][bj]) ++ai;
                else ++bi;
            }
        }
        return res;
    }
};