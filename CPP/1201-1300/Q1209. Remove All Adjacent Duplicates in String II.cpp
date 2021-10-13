class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char, int>> st; // char-cnt
        string res;
        
        for (char c : s) {
            if (st.size() > 0 && st.top().first == c) st.top().second++;
            else st.push({c, 1});
            
            if (st.top().second == k) st.pop();
        }
        
        while (!st.empty()) {
            while (st.top().second--) {
                res.push_back(st.top().first);
            }
            st.pop();
        }
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};