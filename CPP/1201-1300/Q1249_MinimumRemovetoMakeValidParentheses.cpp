class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int open = 0, close = count(s.begin(), s.end(), ')');
        string res = "";
        for (char c : s) {
            if (c == '(') {
                if (open == close) continue; // no more ')', skip this '('
                open++; }
            else if (c == ')') {
                close--;
                if (open == 0) continue; // no '(' to match, skip this ')'
                open--; }
            res += c;
        }
        return res;
    }
};


