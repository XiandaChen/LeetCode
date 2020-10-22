class Solution {
public:
    vector<vector<string>> groupStrings(vector<string>& strings) {
        vector<vector<string>> res;
        // dist from s[0]: <"012", {"abc", "xyz"}>
        unordered_map<string, vector<string>> m; 
        for (string s : strings) {
            string pattern = "";
            for (char c : s) {
                //must add "#": "abc"=>"0#1#2", "am"=>"0#12"
                pattern += to_string((c - s[0] + 26) % 26) + "#"; // "az", "yx"
            }
            m[pattern].push_back(s);
        }
        for (auto a : m) {
            res.push_back(a.second);
        }
        return res;
    }
};
