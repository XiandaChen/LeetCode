class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> umap;
        for (auto str : strs) {
            vector<int> cnt(26, 0);
            string key = "";
            for (auto c : str) ++cnt[c - 'a'];
            for (auto d : cnt) key = key + to_string(d);
            umap[key].push_back(str);
        }
        for (auto x : umap)
            res.push_back(x.second);
        return res;
    }
};