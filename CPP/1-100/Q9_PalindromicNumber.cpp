class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        return (reverseInteger(x) == x);
    }
    int reverseInteger(int x) {
        int res = 0;
        while (x != 0) {
            if (abs(res) > INT_MAX / 10) return 0;
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }
};