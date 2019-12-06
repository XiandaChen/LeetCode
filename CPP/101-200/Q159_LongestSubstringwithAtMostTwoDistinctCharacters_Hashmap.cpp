class Solution {
public:
    int lengthOfLongestSubstringTwoDistinct(string s) {
        unordered_map<char, int> m;
        int res = 0, left = 0; // left: left indx of the window
        for (int i = 0; i < s.size(); ++i) {
            ++m[s[i]];
            while (m.size() > 2) { // size of map = num of distinct chars
                if (--m[s[left]] == 0) m.erase(s[left]); // no char s[left]
                ++left; // move the window forward
            }
            res = max(res, i - left + 1); // update
        }
        return res;
    }
};