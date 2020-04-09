class Solution {
public:
    bool backspaceCompare(string S, string T) {
        string ss, st;  // stack<char> ss, st;
        for (char c : S) {
            // error, if S:"y#f#o##f" => ss:"#f"; T: "y#fo##f" => st:"f"
            // if (!ss.empty() && c == '#') ss.pop_back();
            // else ss.push_back(c);
            if (c != '#') ss.push_back(c); //stack: ss.push(c);
            else {
                if (!ss.empty()) ss.pop_back(); //stack: ss.pop();
            }
        }
        for (char c : T) {
            if (c != '#') st.push_back(c); //stack: st.push(c);
            else {
                if (!st.empty()) st.pop_back(); //stack: st.pop();
            }
        }
        return ss == st;  
    }
};