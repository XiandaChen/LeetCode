class Solution {
public:
    int longestStrChain(vector<string>& words) {
        auto cmp = [] (string & a, string & b) {
            return a.size() < b.size(); // sort increasing
        };
        sort(words.begin(), words.end(), cmp);
        
        int n = words.size(), res = 1;
        unordered_map<string, int> mp; // word-#longestStrChain if including word
        
        for (string word : words) {
            mp[word] = 1;
            for (int i = 0; i < (int)word.size(); i++) {
                string pre = word.substr(0, i) + word.substr(i + 1);  
                if (mp.count(pre)) { // if it is predecessor 
                    mp[word] = max(mp[word], mp[pre] + 1);
                    res = max(res, mp[word]);
                }
            }
        }
        
        return res;
    }
};