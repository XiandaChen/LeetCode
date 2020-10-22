class Solution {
public:
    vector<string> letterCasePermutation(string S) {
        // if (S.size() == 0) return {};
        vector<string> res{""};
        for (char c : S) {
            if (c >= '0' && c <= '9'){
                for (auto & str : res) str.push_back(c);  // &: to update
            }
            else {
                int len = res.size();
                for (int i = 0; i < len; ++i) {
                    res.push_back(res[i]); // res=["a","A"] => res["a",  "A", "a"]
                    res[i].push_back(tolower(c));        // => res["ab", "A", "a"]
                    res[len + i].push_back(toupper(c));  // => res["ab", "A", "aB"]
                }
            }
        }
        return res;
    }
};