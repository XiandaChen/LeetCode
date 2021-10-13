class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int i = 0, j = 0, m = word.size(), n = abbr.size();
        
        while (i < m && j < n) {
            if (isdigit(abbr[j])) {
                if (abbr[j] == '0') return false; // abbr not start with 0
                
                int cnt = 0;
                while (j < n && isdigit(abbr[j])) {
                    cnt = cnt * 10 + (abbr[j++] - '0');
                }
                
                i += cnt;                
            }
            else {
                if (word[i++] != abbr[j++]) return false;
            }
        }
        
        return i == m && j == n;
    }
};