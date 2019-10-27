class Solution {
public:
    int countSubstrings(string s) {
        if (s.empty()) return 0;
        int n = s.size(), res = 0;
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i <= j; ++i) {	// i <= j
                dp[i][j] = (s[i] == s[j]) && 
                        (j - i < 2 || dp[i + 1][j - 1]);
                if (dp[i][j]) ++res;
            }
        }
        return res;
    }
};