class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        unordered_set<string> curset{{s}};
        while (!curset.empty()) {
            unordered_set<string> newset;
            for (auto & t: curset) {
                if (isValid(t)) res.push_back(t);
                // once valid substring is found, stop adding new substring of diff length
                if (!res.empty()) continue;     
                for (int i = 0; i < t.size(); ++i) {
                    if (t[i] != '(' && t[i] != ')') continue;   // skip non-parenthesis char
                    string str = t.substr(0, i) + t.substr(i + 1);
                    newset.insert(str);
                }
            }
            curset = newset;
        }
        return res;
    }
    bool isValid(string s) {
        int cnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') ++cnt;
            // else if (s[i] == ')') --cnt; // error, e.g., "()())("
            else if (s[i] == ')' && --cnt < 0) return false;
        }
        return cnt == 0;
    }
};