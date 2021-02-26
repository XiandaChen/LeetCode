class Solution {
    // recursion and memoization: Time O(n), Space O(n)
    public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        unordered_map<int, int> m; // <indx, ways> for string s[indx, end]
        return ways(s, 0, m);
    }
    // num of ways to decode string s[indx, end]
    int ways (const string &s, int indx, unordered_map<int, int> &m) {
        if (s[indx] == '0') return 0;  // condition 1: s[indx] != '0', must check first
        if (indx >= s.size() - 1) return 1;  // single digit or empty
        if (m.count(indx)) return m[indx];
        
        int w = ways(s, indx + 1, m);  // # ways of s[indx+1, end]
        
        int prefix = (s[indx] - '0') * 10 + (s[indx + 1] - '0');
        if (10 <= prefix && prefix <= 26)  // condition 2: 10 <= s[indx, indx+1] <= 26
            w += ways(s, indx + 2, m);
        
        m[indx] = w;
        return w;
    }
};