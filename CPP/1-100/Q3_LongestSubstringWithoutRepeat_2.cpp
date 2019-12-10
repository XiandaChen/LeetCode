class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> m; // char--last pos
        // left: left indx of last longest substring (window) w.o repeating
        int res = 0, left = -1; 
        
        for (int i = 0; i < s.size(); ++i) {
            // chararcter exist, and its last pos is larger that left indx
            if (m.count(s[i]) && left < m[s[i]]) left = m[s[i]];
            m[s[i]] = i;
            res = max(res, i - left);
        }
        
        return res;
    }
};