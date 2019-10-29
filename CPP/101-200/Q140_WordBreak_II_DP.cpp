class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string, vector<string>> m; // string--breaked words
        return wordBreak(s, wordDict, m);
    }
    vector<string> wordBreak(string s, vector<string> & wordDict, unordered_map<string, vector<string>> & m) {
        if (m.count(s)) return m[s];
        if (s.empty()) return {""}; // {""}, not ""
        vector<string> res;
        for (string word : wordDict) {
            if (s.substr(0, word.size()) != word) continue; // first substr == word
            vector<string> remain = wordBreak(s.substr(word.size()), wordDict, m); // remaining part
            for (string str : remain) {
                res.push_back(word + (str.empty() ? "" : " ") + str);
            }
        }
        return m[s] = res;
    }
};