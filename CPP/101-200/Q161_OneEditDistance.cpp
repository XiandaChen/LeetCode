class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (s.size() < t.size()) swap(s, t); // guarantee s longer than t
        int m = s.size(), n = t.size(), diff = m - n;
        // case 1: if length diff > 1
        if (diff > 1) return false;
        else if (diff == 1) { // case 2: remove one char from longer s
            for (int i = 0; i < n; ++i) {
                if (s[i] != t[i]) // s[i] should be removed
                    return s.substr(i + 1) == t.substr(i); // s[i+1, ..]=t[i..]
            }
        }
        else { // case 3: diff=0, only one replace
            int cnt = 0;
            for (int i = 0; i < m; ++i) 
                if (s[i] != t[i]) ++cnt;
            return cnt == 1;
        }
        return true;
    }
};