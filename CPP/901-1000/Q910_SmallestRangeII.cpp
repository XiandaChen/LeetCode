class Solution {
public:
    int smallestRangeII(vector<int>& A, int K) {
        sort(A.begin(), A.end());
        int n = A.size(), res = A[n - 1] - A[0];
        // small nums A[0:i]: add K; large nums A[i+1, n-1]: add -K
        for (int i = 0; i < n - 1; ++i) { // n-1 for A[i+1]
            int mx = max(A[i] + K, A[n - 1] - K);
            int mn = min(A[0] + K, A[i + 1] - K);
            res = min(res, mx - mn);
        }
        return res;
    }
};