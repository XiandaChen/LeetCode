class Solution {
public:
    string minWindow(string s, string t) {
        string res = "";
        int left = 0, cnt = 0, minlen = INT_MAX; // left: left index of slide window
        unordered_map<char, int> m;
        for (char c : t) ++m[c];
        for (int i = 0; i < s.size(); ++i) {
            if (--m[s[i]] >= 0) ++cnt;  // s[i] is in t
            while (cnt == t.size()) {  // shrink the window
                if (minlen > i - left + 1) { // cur window is smaller than previous one
                    minlen = i - left + 1;
                    res = s.substr(left, minlen);
                }
                if (++m[s[left]] > 0) --cnt; // shift window to right
                ++left;
            }
        }
        return res;
    }
};