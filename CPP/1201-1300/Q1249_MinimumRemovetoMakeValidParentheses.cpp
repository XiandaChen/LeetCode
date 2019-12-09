class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string res = "";
        int close = count(s.begin(), s.end(), ')'); // count all ')'
        int open = 0;
        for (char c : s) {
            if (c == '(') {
                if (open == close) continue; // not ')' later for matching
                ++open;
            }
            else if (c == ')') {
                --close; // decrease close num 
                if (open == 0) continue; // not '(' before for matching 
                --open; // decrease open num after matching
            }
            res += c;
        }
        return res;
    }
};