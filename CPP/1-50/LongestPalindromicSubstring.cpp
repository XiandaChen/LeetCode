class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int n = s.size(), dp[n][n] = {0}, start = 0, len = 1;
        for (int i = 0; i < n; i++) {
            dp[i][i] = 1;
            for (int j = 0; j < i; j++) {
                dp[j][i] = (s[i] == s[j] && (i - j < 2 || dp[j+1][i-1]));
                if (dp[j][i] && len < i - j + 1) {
                    len = i - j + 1;
                    start = j;
                }
            }
        }
        return s.substr(start, len);
    }
};