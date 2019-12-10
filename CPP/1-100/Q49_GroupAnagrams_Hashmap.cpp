class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m; // string--anagrams
        vector<vector<string>> res;
        // group anagrams
        for (string str : strs) {
            string t = str; // we don't want to modify input strs
            sort(t.begin(), t.end());
            m[t].push_back(str);
        }
        // recorde outputs
        for (auto a : m) {
            res.push_back(a.second);
        }
        return res;
    }
};