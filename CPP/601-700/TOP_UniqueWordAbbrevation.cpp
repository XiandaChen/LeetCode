class ValidWordAbbr {
public:
    ValidWordAbbr(vector<string>& dictionary) {
        for (string s : dictionary) {
            string abbr = s;
            if (s.size() > 2) abbr = s[0] + to_string(s.size() -2) + s.back();
            m[abbr].insert(s);
        }
    }
    
    bool isUnique(string word) {
        string abbr = word;
        if (word.size() > 2) abbr = word[0] + to_string(word.size() - 2) + word.back();
        // if no word in dict has the same abbr as word;
        // or, all words in dict that have same abbr of "word" are the same as "word"
        if (!m.count(abbr) || m[abbr].count(word) == m[abbr].size()) return true;
        return false;
    }
private:
    unordered_map<string, unordered_set<string>> m; // abbr--strings
};

/**
 * Your ValidWordAbbr object will be instantiated and called as such:
 * ValidWordAbbr* obj = new ValidWordAbbr(dictionary);
 * bool param_1 = obj->isUnique(word);
 */