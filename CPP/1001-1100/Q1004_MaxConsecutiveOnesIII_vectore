class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        vector<int> m(2, 0);
        int res = 0, left = 0, maxOneCnt = 0;
        for (int i = 0; i < A.size(); ++i) {
            ++m[A[i]];
            maxOneCnt = A[i] == 1 ? maxOneCnt + 1 : maxOneCnt;
            while (i - left + 1 - maxOneCnt > K) {
                maxOneCnt = A[left] == 1 ? maxOneCnt - 1 : maxOneCnt;
                --m[A[left]];
                ++left;
            }
            res = max(res, i - left + 1);
        }
        return res;
    }
};