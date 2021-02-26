class Solution {
public:
    string longestPalindrome(string s) {
        const int n = s.size();
        // &: Lambdas modify local variables through **capture-by-reference*
        auto getLen = [&] (int left, int right) {
            while (left >= 0 && right < n && s[left] == s[right]) {
                --left; ++right;
            }
            return right - left + 1 - 2; // -2: left and right point to non palindromic char
        };
        int start = 0, maxLen = 0;
        for (int i = 0; i < n; ++i) {
            // center of the palindromic: odd, or even positions
            int curLen = max(getLen(i, i), getLen(i, i + 1));
            if (curLen > maxLen) {
                maxLen = curLen;
                start = i - (maxLen - 1) / 2; // update
            }
        }
        return s.substr(start, maxLen);
    }
};