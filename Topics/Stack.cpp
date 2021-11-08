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