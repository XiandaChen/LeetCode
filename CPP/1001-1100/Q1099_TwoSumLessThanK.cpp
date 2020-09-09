class Solution {
public:
    int twoSumLessThanK(vector<int>& A, int K) {
        int res = -1, left = 0, right = A.size() - 1;
        sort(A.begin(), A.end());
        while (left < right) {
            int cursum = A[left] + A[right];
            if (cursum >= K) --right;
            else {
                res = max(res, cursum);
                ++left;
            }
        }
        return res;
    }
};