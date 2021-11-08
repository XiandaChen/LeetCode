// 5. Longest Palindromic Substring
// dp[i,j]: substring from i to j (inclusive) is palindromic
// dp[i,j]	= 1									if j == i
//			= (s[j] == s[i])					if j = i + 1
//			= (s[j] == s[i]) && dp[i+1, j-1]	if j > i + 1
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

// 647. Number of Palindromic Substrings
// DP
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

// 131. Palindrome Partitioning


// 9. Palindrome Number
// Reverse integer function
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        return (reverseInteger(x) == x);
    }
    int reverseInteger(int x) {
        int res = 0;
        while (x != 0) {
            if (abs(res) > INT_MAX / 10) return 0; // must check overflow
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }
};

// 125. Valid Palindrome
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            if (!isalnum(s[i])) ++i;
            else if (!isalnum(s[j])) --j;
            else if (tolower(s[i]) != tolower(s[j])) return false;
            else {++i; --j;}
        }
        return true;
    }
};
