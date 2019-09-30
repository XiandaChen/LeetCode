class Solution {
public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};  // dont forget to check empty
        vector<string> dict = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> res = {""};		// initiate to "": for (string s : res) 
        for (int i = 0; i < digits.size(); i++) {
            string str = dict[digits[i] - '0'];     // digit to int
            vector<string> tmp;
            for (string s : res) {
                for (int j = 0; j < str.size(); j++)
                    tmp.push_back(s + str[j]);      
            }
            res = tmp;
        }
        return res;
    }
};