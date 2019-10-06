class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set wordSet(wordDict.begin(), wordDict.end());
        vector<int> memo(s.size(), -1); // initial memo[]
        return wordBreak(s, wordSet, 0, memo);
    }
    bool wordBreak(string s, unordered_set<string> & wordSet, int start, vector<int> & memo) {
        if (start >= s.size()) return true;
        if (memo[start] != -1) return memo[start];
        for (int i = start + 1; i <= s.size(); ++i) {
            if (wordSet.count(s.substr(start, i - start)) && wordBreak(s, wordSet, i, memo))
                return memo[start] = 1;
        }
        return memo[start] = 0;
    }
};