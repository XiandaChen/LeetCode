class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> m{{'I', 1}, {'V', 5}, {'X', 10}, 
                                   {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
        int res = 0;
        // roman numbers written largest to smallest from left to right
        for (int i = 0; i < s.size(); ++i) {
            int val = m[s[i]];
            // the last one, or larger than later one
            if (i == s.size() - 1 || m[s[i]] >= m[s[i+1]]) res += val;
            else res -= val; // "MCM": + 1000 - 100 + 1000
        }
        return res;
    }
};