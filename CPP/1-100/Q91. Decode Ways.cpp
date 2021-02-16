class Solution {
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        unordered_map<int, int> m; // indx-decodeWays for s[indx:]
        return helper(s, 0, m);
    }
    int helper(string s, int indx, unordered_map<int, int>& m) {
        if (s[indx] == '0') return 0; // string starts with a zero, it can't be decoded
        if (indx >= s.size() - 1) return 1; // reach the end
        if (m.count(indx)) return m[indx];
        int res = helper(s, indx + 1, m);
        string ss = s.substr(indx, 2);
        if (stoi(ss) <= 26) res += helper(s, indx + 2, m);
        m[indx] = res;
        return res;
    }
};