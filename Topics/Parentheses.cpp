// 20. Valid Parentheses
// Stack
class Solution {
public:
    bool isValid(string s) {
        stack<char> parentheses;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')  parentheses.push(s[i]);
            else {
                if (parentheses.empty()) return false;
                if (s[i] == ')' && parentheses.top() != '(') return false;
                if (s[i] == '}' && parentheses.top() != '{') return false;
                if (s[i] == ']' && parentheses.top() != '[') return false;
                parentheses.pop();
            }
        }
        return parentheses.empty();
    }
};

// 22. Generate Parentheses
// DFS
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        generateParenthesisDFS(n, n, "", res);
        return res;
    }
    // left/right: remaining num of left/right bracket
    void generateParenthesisDFS(int left, int right, string out, vector<string> &res) {
        if (left > right) return;
        if (left == 0 && right == 0)
            res.push_back(out);
        else {
            if (left > 0) generateParenthesisDFS(left-1, right, out+'(', res);
            if (right > 0) generateParenthesisDFS(left, right-1, out+')', res);
        }
    }
};

// 32. Longest Valid Parentheses
// Stack
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxlen = 0;
        stack<int> st;
        st.push(-1);	// start by index -1 in stack
        for (int i = 0 ; i < (int)s.size(); i++) {
            if (s[i] == '(') st.push(i);
            else {
                st.pop();
                if (st.empty()) st.push(i); // stack empty
                else maxlen = max(maxlen, i - st.top());
            }
        }
        return maxlen;
    }
};

// 301. Remove Invalid Parentheses
// unordered_set
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        unordered_set<string> curset{{s}};
        while (!curset.empty()) {
            unordered_set<string> newset;	// new set of substring of one-less length
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

// 1249. Minimum Remove to Make Valid Parentheses
// Input: s = "a)b(c)d";  Output: "ab(c)d"
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