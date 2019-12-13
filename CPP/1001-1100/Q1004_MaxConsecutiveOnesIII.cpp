class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        int left = 0, zeros = 0, res = 0;
        // sliding window: [left, right]
        for (int right = 0; right < A.size(); ++right) {
            if (A[right] == 0) ++zeros;
            // shift the window to right if zeros > K
            while (zeros > K) {
                if (A[left++] == 0) --zeros;
            }
            // update res
            res = max(res, right - left + 1);
        }
        return res;
    }
};