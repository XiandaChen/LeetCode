class Solution {
public:
    string reverseWords(string s) {
        istringstream is(s);
        s = "";
        string tmp = "";
        while (getline(is, tmp, ' ')) {
            if (tmp.empty()) continue; // getline get one space each time
            s = (s.empty()) ? tmp : (tmp + " " + s);
        }
        return s;
    }
};