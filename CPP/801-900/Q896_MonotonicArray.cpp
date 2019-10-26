class Solution {
public:
    bool isMonotonic(vector<int>& A) {
        int inc = 1, dec = 1, n = A.size();
        for (int i = 1; i < n; ++i) {
            inc += (A[i - 1] <= A[i]);
            dec += (A[i - 1] >= A[i]);
        }
        return (inc == n) || (dec == n);
    }
};