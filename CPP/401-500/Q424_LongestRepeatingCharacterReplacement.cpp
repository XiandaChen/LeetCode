class Solution {
public:
    int characterReplacement(string s, int k) {
        // unordered_map<char, int> m;   // method 1
        vector<int> m(26, 0);           // method 2
        int res = 0, left = 0, maxCnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            // max occurrence in sliding window
            // maxCnt = max(maxCnt, ++m[s[i]]); 
            maxCnt = max(maxCnt, ++m[s[i] - 'A']);
            while (i - left + 1 - maxCnt > k) { // at most K changes
                // if (--m[s[left]] == 0) m.erase(s[left]);
                --m[s[left] - 'A'];
                ++left;
            }
            res = max(res, i - left + 1);
        }
        return res;
    }
};