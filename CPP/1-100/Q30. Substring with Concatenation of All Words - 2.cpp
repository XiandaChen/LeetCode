class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        unordered_map<string, int> wordCnt;
        int num = words.size(), len = words[0].size();
        int lens = s.size(), lenw = num * len;
        vector<int> res;
        
        for (auto word : words) wordCnt[word]++;
        
        for (int i = 0; i <= lens - lenw; i++) {
            unordered_map<string, int> tmp = wordCnt;
            
            // check if ss is concatenation of words
            for (int j = 0; j < num; j++) {
                string ss = s.substr(i + j * len, len); // substring
                
                if (--tmp[ss] < 0) break; // ss not in words
                
                if (j == num - 1) res.push_back(i);
            }
        }
        
        return res;
    }
};