class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) return INT_MAX;
        long m = labs(dividend), n = labs(divisor), res = 0; // must be long, not int
        int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
        if (n == 1) return (sign == 1) ? m : -m; 
        while (m >= n) {
            long t = n, q = 1; // initial q = 1, type long
            while (m >= (t << 1)) { // dividend larger than two-time t
                t <<= 1;
                q <<= 1;    // quotient plus two
            }
            res += q;
            m -= t;
        }
        return (sign == 1) ? res : -res;
    }
};