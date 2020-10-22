class Solution {
public:
    bool isNumber(string s) {
        // e/E: at most one time; if exists, must have digit before, char right before must digit or dot
        // .: at most one time; if exists, must before e/E, and have digit
        // +/-: must be at the beginning or right after e/E, not two sign come together
        bool eExist = false, dotExist = false, signExist = false, digitExist = false;
        int left = 0, right = s.size() - 1;
        // 1. remove empty space
        while (left <= right && s[left] == ' ') ++left; 
        while (left <= right && s[right] == ' ') --right;
        // 2. the first char must be: sign +/-, digit, or dot
        if (s[left] == '+' || s[left] == '-') signExist = true;
        else if (isdigit(s[left])) digitExist = true;
        else if (s[left] == '.') dotExist = true;
        else return false;
        // 3. chars in the middle
        for (int i = left + 1; i < right; ++i) {
            if (isdigit(s[i])) digitExist = true;
            else if (s[i] == 'e' || s[i] == 'E') {
                if (!eExist && digitExist && (isdigit(s[i-1]) || s[i-1] == '.'))
                    eExist = true;
                else return false;
            }
            else if (s[i] == '.') {
                if (!dotExist && !eExist) dotExist = true;
                else return false;
            }
            else if (s[i] == '+' || s[i] == '-') {
                if (s[i-1] != 'e' && s[i-1] != 'E') return false;
            }
            else return false;
        }
        // 4. the last char must be: digit, or dot
        if (isdigit(s[right])) return true;
        else if (s[right] == '.' && !dotExist && !eExist && digitExist) return true;
        else return false;
    }
};