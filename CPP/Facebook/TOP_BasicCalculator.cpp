class Solution {
public:
    int calculate(string s) {
        if (s.empty()) return 0; // corner case
        int n = s.size(), res = 0, lastNum = 0, curNum = 0;
        char lastOp = '+';  // previous operator: 1+2*3 => 0+1+2*3
        for (int i = 0; i < n; ++i) {
            char curChar = s[i];
            if ('0' <= curChar && curChar <= '9') curNum = curNum * 10 + (curChar - '0');
            if (i == n - 1 || curChar == '+' || 
                curChar == '-' || curChar == '*' || curChar == '/') {
                if (lastOp == '+' || lastOp == '-') {
                    res += lastNum;
                    lastNum = (lastOp == '+') ? curNum : -curNum;
                }
                else if (lastOp == '*') { lastNum *= curNum; }
                else if (lastOp == '/') { lastNum /= curNum; }
                lastOp = curChar;
                curNum = 0;
            }
        }
        return res + lastNum;  // must, add the very last num
    }
};