class Solution {
public:
    int countSubstrings(string s) {
        if (s.empty()) return 0;
        int n = s.size(), res = 0;
        for (int i = 0; i < n; ++i) {
            countSubstrings(s, i, i, res); // palindromic with odd num
            countSubstrings(s, i, i + 1, res); // palindromic with even num
        }
        return res;
    }
    void countSubstrings(string s, int l, int r, int & res) {
        while (l >= 0 && r < s.size() && s[l--] == s[r++]) ++res;
    }
};