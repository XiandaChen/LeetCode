class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (s.size() < t.size()) return isOneEditDistance(t, s);
        int m = s.size(), n = t.size(), dif = m - n;
        if (dif > 1) return false;
        else if (dif == 1) { // delete one from the longer s
            for (int i = 0 ; i < n; ++i) { // n, not m
                if (s[i] != t[i]) return s.substr(i + 1) == t.substr(i);
            }
        }
        else { // m == n, replace one
            int cnt = 0;
            for (int i = 0; i < m; ++i) {
                if (s[i] != t[i]) ++cnt;
            }
            return cnt == 1;
        }
        return true;
    }
};