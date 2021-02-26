// dp[i]: ways to decode string s[0, i]
// = 0			if s[i] not valid, and s[i-1, i] not valid
// = dp[i-1]	if s[i] valid
// = dp[i-2]	if s[i-1, i] valid
// = dp[i-1] + dp[i-2]		if s[i] valid, and s[i-1, i] valid
class Solution {
    // DP: Time O(n), Space O(1)
    public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        // vector<int> dp(s.size() + 1, 0); // not used, otherwise Space O(n)
        
        int w1 = 1, w2 = 1; // i = 0, dp[i-1]=1, dp[i-2]=1
        for (int i = 1; i < (int)s.size(); ++i) { // start from i=1
            int w = 0; // ways to decode string s[0, i]
            if (!isValid(s[i]) && !isValid(s[i - 1], s[i])) w = 0;
            if (isValid(s[i])) w = w1;
            if (isValid(s[i - 1], s[i])) w += w2;
            
            w2 = w1;
            w1 = w;
        }
        
        return w1;
    }
    bool isValid(const char c) {return c != '0';}
    bool isValid(const char c1, const char c2) {
        int num = (c1 - '0') * 10 + (c2 - '0');
        return (10 <= num) && (num <= 26);
    }
};