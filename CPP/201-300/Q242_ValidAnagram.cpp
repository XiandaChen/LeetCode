class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> s_cnt(26), t_cnt(26);
        for (char c : s) ++s_cnt[c - 'a'];
        for (char c : t) ++t_cnt[c - 'a'];
        return s_cnt == t_cnt;
    }
};