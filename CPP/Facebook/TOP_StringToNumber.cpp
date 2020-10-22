class Solution {
public:
    int myAtoi(string s) {
        if (s.empty()) return 0;
        int sign = 1, num = 0, n = s.size(), i = 0;
        while (i < n && s[i] == ' ') ++i;
        if (s[i] == '+' || s[i] == '-') {
            sign = (s[i] == '+') ? 1 : -1;
            ++i;
        }
        while (i < n && isdigit(s[i])) {
            // check INT_MAX
            if (num > INT_MAX / 10 || (num == INT_MAX / 10 && s[i] > '7'))
                return (sign == 1) ? INT_MAX : INT_MIN;
            num = num * 10 + (s[i] - '0');
            ++i;
        }
        return sign * num;
    }
};