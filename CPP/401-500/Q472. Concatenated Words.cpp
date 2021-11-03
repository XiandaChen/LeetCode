class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        if (words.size() <= 2) return {};
        
        unordered_set<string> wordSet(words.begin(), words.end());
        vector<string> res;
        
        for (string word : words) { // NOTE, words, not wordSet
            // concatenated word: at least two shorter words 
            wordSet.erase(word);
            int len = word.size();
            if (len == 0) continue;
            
            vector<bool> dp(len + 1, false); // dp[i]: word[0:i] is concatenatable
            dp[0] = true;
            for (int i = 0; i < len + 1; i++) {
                for (int j = 0; j < i; j++) {
                    if (dp[j] && wordSet.count(word.substr(j, i - j))) {
                        dp[i] = true;
                        break;
                    }
                }
            }
            
            if (dp.back()) res.push_back(word);
            wordSet.insert(word);
        }
        
        return res;
    }
};
