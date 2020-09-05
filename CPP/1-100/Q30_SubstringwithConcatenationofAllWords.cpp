class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if (s.empty() || words.empty()) return {};
        vector<int> res;
        int cnt = words.size(), len = words[0].size();
        unordered_map<string, int> wordCnt;
        for (auto w : words) ++wordCnt[w];
        for (int i = 0; i <= (int)s.size() - cnt * len; ++i) { // must be '<='; and (int): s="a",words=["a","a"]
            unordered_map<string, int> strCnt;
            for (int j = 0; j < cnt; ++j) {
                string word = s.substr(i + j * len, len);
                if (!wordCnt.count(word)) break;  // word not in words
                ++strCnt[word];
                if (strCnt[word] > wordCnt[word]) break;  // word already checked
                
                if (j == cnt - 1) res.push_back(i); // store indx after finding all words
            }
        }
        return res;
    }
};

