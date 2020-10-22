class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> m ;
        int left = 0, cnt = 0, minlen = INT_MAX;
        string res = "";
        for (char c : t) ++m[c];
        for (int i = 0; i < s.size(); ++i) {
            if (--m[s[i]] >= 0) ++cnt; // s[i] in t
            while (cnt == t.size()) {
                if (i - left + 1 < minlen) {
                    minlen = i - left + 1;
                    res = s.substr(left, minlen);
                }
                if (++m[s[left]] > 0) --cnt; // sliding windwo to right
                ++left;
            }
        }
        return res;
    }
};