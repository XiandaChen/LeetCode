class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.empty()) return {};
        vector<int> res, tp(128, 0), ts(128, 0); // ts, tp: 128 -> ASCII value: 97(a)-122(z)
        for (int i = 0; i < (int)p.size(); ++i) {
            ++tp[p[i]]; ++ts[s[i]]; 
        }
        if (tp == ts) res.push_back(0); // two table match, and save indx 0
        for (int i = p.size(); i < (int)s.size(); ++i) {
            ++ts[s[i]]; --ts[s[i - p.size()]]; // remove leftmost char and add new one
            if (tp == ts) res.push_back(i - p.size() + 1); // indx: i-p.size()+1
        }
        return res;
    }
};