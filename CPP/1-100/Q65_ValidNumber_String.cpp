class Solution {
public:
    bool isNumber(string s) {
        int len = s.size(), left = 0, right = len - 1;
        // eExisted: 'e/E' must be at most one time
        // dotExisted: '.' must be at most one time
        // digitExisted: at least one digit before 'e/E' if 'e/E' exists
        bool eExisted = false, dotExisted = false, digitExisted = false;
        
        // pre-process to remove space at the front and end
        while (s[left] == ' ') ++left;
        while (s[right] == ' ') --right;
        
        // process the first char: must be '.', digit,  or '+/-'
        if (s[left] == '.') dotExisted = true;
        else if ('0' <= s[left] && s[left] <= '9') digitExisted = true;
        else if (s[left] != '+' && s[left] != '-') return false; 
        
        // process chars in the middle
        for (int i = left + 1; i < right; ++i) {
            if ('0' <= s[i] && s[i] <= '9') digitExisted = true;
            else if (s[i] == 'e' || s[i] == 'E') {
                // 'e/E' must be at most one time
                // must have digit before 'e/E'
                // must be digit or '.' right before 'e/E'
                if (!eExisted && digitExisted && 
                    ('0' <= s[i - 1] && s[i - 1] <= '9' || s[i - 1] == '.'))
                    eExisted = true;
                else    return false;
            }
            else if (s[i] == '+' || s[i] == '-') {
                // '+/-' occur in the middle must be after 'e/E'
                if (s[i - 1] != 'e' && s[i - 1] != 'E') return false;
            }
            else if (s[i] == '.') {
                // '.' must be at most one time
                // '.' must not be after 'e/E'
                if (!dotExisted && !eExisted) dotExisted = true;
                else return false;
            }
            else return false;
        }
        
        // process the last char: must be digit or '.'
        if ('0' <= s[right] && s[right] <= '9') return true;
        else if (s[right] == '.' && !dotExisted && !eExisted && digitExisted) return true;
        else return false;
    }
};