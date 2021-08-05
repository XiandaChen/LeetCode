class Solution {
public:
    int calculate(string s) {
        int n = s.size(), num = 0, res = 0;
        char preOP = '+';
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            
            if ('0' <= c && c <= '9') {
                num = num * 10 + (c - '0');
            }
            else if (c == '(') {
                int j = i, cnt = 0; 
                for (; i < n; ++i) {
                    if (s[i] == '(') ++cnt;
                    if (s[i] == ')') --cnt;
                    if (cnt == 0) break;
                }
                num = calculate(s.substr(j + 1, i - j - 1));
            }
            
            if (c == '+' || c == '-' || i == n - 1) {
                switch (preOP) {
                    case '+': res += num; break;
                    case '-': res -= num; break;
                }
                num = 0;
                preOP = c;
            }
        }
        return res;
    }
};
