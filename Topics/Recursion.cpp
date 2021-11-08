// Recursion: all possible combinations/cases

// 17. Letter Combinations of a Phone Number
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

// 39. Combination Sum
// Find all unique combinations in candidates where the candidate numbers sums to target.
class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> res;
        vector<int> out;
        combinationSumDFS(candidates, target, 0, out, res);
        return res;
    }
    void combinationSumDFS(vector<int>& candidates, int target, int start, vector<int>& out, vector<vector<int>>& res) {
        if (target < 0) return;
        if (target == 0) {res.push_back(out); return;}
        for (int i = start; i < candidates.size(); i++) {
            out.push_back(candidates[i]);
            combinationSumDFS(candidates, target - candidates[i], i, out, res);
            out.pop_back();
        }
    }
};

// 282. Expression Add Operators, DFS
// Input: num = "105", target = 5;    Output: ["1*0+5","10-5"]
class Solution {
public:
    vector<string> addOperators(string num, int target) {
        vector<string> res;
        helper(num, target, 0, 0, "", res);
        return res;
    }
    void helper(string numstr, int target, long value, int pre_num, 
                string equation, vector<string> & res) {
        // iterate to the end of given num, and value equals to target
        if (numstr.size() == 0 && value == target) {
            res.push_back(equation); return;
        }
        // "105": "1" "05"; "10" "5"; "105" ""
        for (int i = 1; i <= numstr.size(); ++i) { // "i=1" and "<=", as for substr()
            string cur = numstr.substr(0, i); // substr as a num
            string next = numstr.substr(i); // add operator b/w cur and next
            
            if (cur.size() > 1 && cur[0] == '0') return; // num not start with zero
            
            if (equation.size() == 0) { // initialize equation with cur substr in the front
                helper(next, target, stoll(cur), stoll(cur), cur, res);
                continue;
            }
            
            // For "*", it needs trace back the pre_number
            helper(next, target, value + stoll(cur), stoll(cur), equation + "+" + cur, res);
            helper(next, target, value - stoll(cur), -stoll(cur), equation + "-" + cur, res);
            helper(next, target, value - pre_num + pre_num * stoll(cur), pre_num * stoll(cur), 
                   equation + "*" + cur, res);
        }
    }
};

// 93. Restore IP Addresses
// Input: "25525511135";  Output: ["255.255.11.135", "255.255.111.35"]
class Solution {
public:
    vector<string> restoreIpAddresses(string s) {
        vector<string> res;
        restore(s, 4, "", res); // k=4: still need 4 partition
        return res;
    }
    void restore(string s, int k, string out, vector<string> & res) {
        if (k == 0) { // we have 4 parts
            if (s.size() == 0) res.push_back(out);
        }
        else { // partition s 
            for (int i = 1; i <= 3; ++i) {
                if (s.size() >= i && isValid(s.substr(0, i))) {
                    if (k == 1) // last partition
                        restore(s.substr(i), k - 1, out + s.substr(0, i), res);
                    else // not the last partition
                        restore(s.substr(i), k - 1, out + s.substr(0, i) + '.', res);
                }
            }
        }
    }
    bool isValid(string s) {
        // IP add part has size 1-3
        if (s.empty() || s.size() > 3 || (s.size() > 1 && s[0] == '0')) return false;
        int val = atoi(s.c_str()); // c_str() pointer of an array(string)
        return 0 <= val && val <= 255;
    }
};