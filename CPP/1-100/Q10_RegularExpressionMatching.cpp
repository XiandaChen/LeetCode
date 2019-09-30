class Solution {
public:
    bool isMatch(string s, string p) {
        if (p.size() == 0) 
            return (s.size() == 0);
        
        if (p.size() == 1) 
            return ((s.size() == 1) && (p[0] == '.' || p[0] == s[0]));
        
        if (p[1] != '*') {  // recurse searching until 2nd char in p is *
            if (s.size() == 0) 
                return false;
            return ((p[0] == '.' || p[0] == s[0]) && isMatch(s.substr(1), p.substr(1)));
        }
        
        while (s.size() != 0 && (p[0] == '.' || p[0] == s[0])) {
            if (isMatch(s, p.substr(2)))    // if true when remove first two char in p
                return true;
            s = s.substr(1);    // else, remove first char is and then recurse
        }
        
        return isMatch(s, p.substr(2));
    }
};