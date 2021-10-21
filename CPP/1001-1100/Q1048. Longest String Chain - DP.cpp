class Solution {
public:
    int longestStrChain(vector<string>& words) {
        auto cmp = [] (string & a, string & b) {
            return a.size() < b.size(); // sort increasing
        };
        sort(words.begin(), words.end(), cmp);
        
        int n = words.size(), res = 1;
        
        vector<int> dp(n, 1);
        
        for (int i = 1; i < n; i++) {
            for (int j = i - 1; j >= 0; j--) {
                if (words[j].size() + 1 < words[i].size()) break; // only one char diff
                if (words[j].size() == words[i].size()) continue;
                
                // if words[j] is predecessor of words[i]
                if (helper(words[j], words[i])) {
                    dp[i] = max(dp[i], dp[j] + 1);
                    res = max(res, dp[i]);
                }
            }
        }
        
        return res;
    }
    
    bool helper(string word1, string word2) {
        int m = word1.size(), n = word2.size(), i = 0;
        for (int j = 0; j < n; j++) {
            if (word2[j] == word1[i]) ++i;
        }
        return i == m;
    }
};