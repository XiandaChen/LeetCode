// decode string
// Input: s = "g3[a2[c]]", Output: "gaccaccacc"
class Solution {
public:
    string decodeString(string s) {
        stack<string> st_str;
        stack<int> st_num;
        string tmp = "";
        int cnt =  0;
        for (char c : s) {
            if (c >= '0' && c <= '9') {
                cnt = cnt * 10 + (c - '0');
            }
            else if (c == '[') { // push in tmp for decode
                st_num.push(cnt);
                st_str.push(tmp);
                cnt = 0;
                tmp.clear();
            }
            else if (c == ']') {
                int num = st_num.top(); st_num.pop();
                for (int i = 0; i < num; ++i) {
                    st_str.top() += tmp; // top() returns a reference to the top element
                }
                tmp = st_str.top(); st_str.pop(); // [str] is decoded and stored in tmp
            }
            else {
                tmp += c;
            }
        }
        return st_str.empty() ? tmp : st_str.top() + tmp; // for s="2[abc]3[cd]ef", st_str is empty        
    }
};

