class Solution {
public:
    double myPow(double x, int n) {
        return n >= 0 ? myPowRec(x, n) : 1.0 / myPowRec(x, n);
    }
    double myPowRec(double x, int n) {
        if (n == 0) return 1;
        // (-1 % 2)==1; (-4 % 2)==0
        return myPowRec(x * x, n / 2) * (n % 2 ? x : 1);
    }
};