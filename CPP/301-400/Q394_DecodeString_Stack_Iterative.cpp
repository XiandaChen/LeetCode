class Solution {
public:
    string decodeString(string s) {
        string t = "";
        stack<int> st_num;
        stack<string> st_str;
        int cnt = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] >= '0' && s[i] <= '9') {
                cnt = 10 * cnt + s[i] - '0';
            }
            else if (s[i] == '[') { // push in t for decode
                st_num.push(cnt);
                st_str.push(t);
                cnt = 0; t.clear();
            }
            else if (s[i] == ']') {
                int k = st_num.top(); st_num.pop();
                for (int i = 0; i < k; ++i) {
                    st_str.top() += t; // top() returns a reference to the top element
                }
                t = st_str.top(); st_str.pop(); // [str] is decoded and stored in t
            }
            else {
                t += s[i];
            }
        }
        return (st_str.empty()) ? t : st_str.top(); // for s="2[abc]3[cd]ef", st_str is empty
    }
};