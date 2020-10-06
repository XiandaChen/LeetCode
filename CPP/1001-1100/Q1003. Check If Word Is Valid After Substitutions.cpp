class Solution {
public:
    bool isValid(string s) {
        stack<char> st;
        for (int i = 0; i < (int)s.size(); ++i) {
            st.push(s[i]);
            if (st.top() == 'c') {
                if (st.size() < 3) return false;
                st.pop(); // pop out 'c'
                // check if previously pushed ones are 'b' and 'a'
                char b = st.top(); st.pop();
                char a = st.top(); st.pop();
                if (a != 'a' or b != 'b') return false;
            }
        }
        if (st.empty()) return true;
        return false;
    }
};