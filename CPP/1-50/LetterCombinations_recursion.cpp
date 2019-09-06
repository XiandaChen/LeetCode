class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};  // dont forget to check empty
        vector<string> dict = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> res = {};  // initiate to {} : recursion
        
        letterCombinationsDFS(digits, dict, res, 0, "");    // starting: level=0
        
        return res;
    }
    void letterCombinationsDFS(string & digits, vector<string> & dict, vector<string> & res, int level, string out) {
        if (level == digits.size()) {
            res.push_back(out);
            return;
        }
        string str = dict[digits[level] - '0'];
        for (int i = 0; i < str.size(); i++) {
            letterCombinationsDFS(digits, dict, res, level + 1, out + str[i]);
        }
    }
};