// 258. Add Digits (Digital root of a num)
// Input: 38;   Output: 2 
// Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.
class Solution {
public:
    int addDigits(int num) {
        while (num >= 10) { // must be >=
            int sum = 0;
            while (num) {
                sum += (num % 10);
                num /= 10;
            }
            num = sum;
        }
        return num;
    }
};