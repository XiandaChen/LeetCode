class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size(), res = 0;
        for (int i = 0; i < n; i++) {
            int j = i - 1, k = i + 1;
            while (j >= 0 && s[j] != s[i]) j--;
            while (k < n && s[k] != s[i]) k++;
            res += (i - j) * (k - i); // (i-j)*(k-i): #substrings that s[i] appears
        }
        return res;
    }
