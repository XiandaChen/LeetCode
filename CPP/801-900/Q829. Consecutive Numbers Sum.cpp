class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int res = 1; // the array of [n]
        for (int i = 2; i < sqrt(2 * n); i++) {
            if ((n - i * (i - 1) / 2) % i == 0) res++;
        }
        return res;
    }
};