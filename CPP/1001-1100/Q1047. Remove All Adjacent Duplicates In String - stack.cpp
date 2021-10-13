class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        string res;
        
        for (char c : s) {
            if (st.empty()) st.push(c);
            else if (st.top() == c) st.pop(); // remove adjacent duplicates
            else st.push(c);
        }
        
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};