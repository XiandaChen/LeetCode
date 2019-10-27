class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int n = s.size(), start = 0, len = 1;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i <= j; ++i) {	// i <= j
                dp[i][j] = (s[i] == s[j]) &&
                        (j - i < 2 || dp[i + 1][j - 1]); // dp
                if (dp[i][j] && (len < j - i + 1)) {
                    len = j - i + 1;
                    start = i;
                }
            }
        }
        return s.substr(start, len);
    }
};