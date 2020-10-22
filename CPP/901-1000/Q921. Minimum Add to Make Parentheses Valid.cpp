class Solution {
public:
    int minAddToMakeValid(string S) {
        stack<char> st;
        for (char c : S) {
            if (c == ')' && !st.empty() && st.top() == '(') st.pop(); // !st.empty() must
            else st.push(c);
        }
        return st.size();
    }
};