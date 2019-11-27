class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        unordered_set<string> visited {{s}};    // record had-been-visited substring
        queue<string> q{{s}};   // record new-generated substrings after removing some parentheses
        bool found = false;
        while (!q.empty()) {
            string t = q.front(); q.pop();
            if (isValid(t)) {
                res.push_back(t);
                found = true;
               // continue;     // error, "()())()" output: ["(())()","()()()","()()","(())","()",""]
            }
			// once valid substring is found, stop adding new substring of diff length
            if (found) continue;    // "()())()" output: ["(())()","()()()"]
            for (int i = 0; i < t.size(); ++i) {
                if (t[i] != '(' && t[i] != ')') continue;   // skip non-parenthesis char
                string str = t.substr(0, i) + t.substr(i + 1);
                if (!visited.count(str)) {  // check visited, not q
                    q.push(str);            // add new-generated substring
                    visited.insert(str);    // mark as visited
                }
            }
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