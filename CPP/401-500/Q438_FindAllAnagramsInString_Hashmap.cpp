class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.empty()) return {};
        unordered_map<char, int> ms, mp; // char-num
        vector<int> res;
        for (int i = 0; i < p.size(); ++i) {
            ++ms[s[i]]; ++mp[p[i]];
        }
        // if ms==mp
        if (ms == mp) res.push_back(0);
        for (int i = p.size(); i < s.size(); ++i) {
            // move the window forward by one char
            if (--ms[s[i - p.size()]] == 0) ms.erase(s[i - p.size()]);
            ++ms[s[i]];
            if (ms == mp) res.push_back(i - p.size() + 1);
        }
        return res;
    }
};