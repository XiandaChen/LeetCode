// ==== 1. parentheses ===
// 20. Valid Parentheses
// Stack
class Solution {
public:
    bool isValid(string s) {
        stack<char> parentheses;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(' || s[i] == '{' || s[i] == '[')  parentheses.push(s[i]);
            else {
                if (parentheses.empty()) return false;
                if (s[i] == ')' && parentheses.top() != '(') return false;
                if (s[i] == '}' && parentheses.top() != '{') return false;
                if (s[i] == ']' && parentheses.top() != '[') return false;
                parentheses.pop();
            }
        }
        return parentheses.empty();
    }
};

// 22. Generate Parentheses
// DFS
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        generateParenthesisDFS(n, n, "", res);
        return res;
    }
    // left/right: remaining num of left/right bracket
    void generateParenthesisDFS(int left, int right, string out, vector<string> &res) {
        if (left > right) return;
        if (left == 0 && right == 0)
            res.push_back(out);
        else {
            if (left > 0) generateParenthesisDFS(left-1, right, out+'(', res);
            if (right > 0) generateParenthesisDFS(left, right-1, out+')', res);
        }
    }
};

// 32. Longest Valid Parentheses
// Stack
class Solution {
public:
    int longestValidParentheses(string s) {
        int maxlen = 0;
        stack<int> st;
        st.push(-1);	// start by index -1 in stack
        for (int i = 0 ; i < (int)s.size(); i++) {
            if (s[i] == '(') st.push(i);
            else {
                st.pop();
                if (st.empty()) st.push(i); // stack empty
                else maxlen = max(maxlen, i - st.top());
            }
        }
        return maxlen;
    }
};

// 301. Remove Invalid Parentheses
// unordered_set
class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> res;
        unordered_set<string> curset{{s}};
        while (!curset.empty()) {
            unordered_set<string> newset;	// new set of substring of one-less length
            for (auto & t: curset) {
                if (isValid(t)) res.push_back(t);
                // once valid substring is found, stop adding new substring of diff length
                if (!res.empty()) continue;     
                for (int i = 0; i < t.size(); ++i) {
                    if (t[i] != '(' && t[i] != ')') continue;   // skip non-parenthesis char
                    string str = t.substr(0, i) + t.substr(i + 1);
                    newset.insert(str);
                }
            }
            curset = newset;
        }
        return res;
    }
    bool isValid(string s) {
        int cnt = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') ++cnt;
            // else if (s[i] == ')') --cnt; // error, e.g., "()())("
            else if (s[i] == ')' && --cnt < 0) return false;
        }
        return cnt == 0;
    }
};

// 1249. Minimum Remove to Make Valid Parentheses
// Input: s = "a)b(c)d";  Output: "ab(c)d"
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        string res = "";
        int close = count(s.begin(), s.end(), ')'); // count all ')'
        int open = 0;
        for (char c : s) {
            if (c == '(') {
                if (open == close) continue; // not ')' later for matching
                ++open;
            }
            else if (c == ')') {
                --close; // decrease close num 
                if (open == 0) continue; // not '(' before for matching 
                --open; // decrease open num after matching
            }
            res += c;
        }
        return res;
    }
};

//========== 2. Recursion =======
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

// ======= 3. palindromic =====
// 5. Longest Palindromic Substring
// dp[i,j]: substring from i to j (inclusive) is palindromic
// dp[i,j]	= 1									if j == i
//			= (s[j] == s[i])					if j = i + 1
//			= (s[j] == s[i]) && dp[i+1, j-1]	if j > i + 1
class Solution {
public:
    string longestPalindrome(string s) {
        if (s.empty()) return "";
        int n = s.size(), start = 0, len = 1;
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i <= j; ++i) {	// i <= j
                dp[i][j] = (s[i] == s[j]) &&
                        (j - i < 2 || dp[i + 1][j - 1]); // dp
                if (dp[i][j] && (len < j - i + 1)) {
                    len = j - i + 1;
                    start = i;
                }
            }
        }
        return s.substr(start, len);
    }
};

// 647. Number of Palindromic Substrings
// DP
class Solution {
public:
    int countSubstrings(string s) {
        if (s.empty()) return 0;
        int n = s.size(), res = 0;
        vector<vector<bool>> dp(n, vector<bool>(n));
        for (int j = 0; j < n; ++j) {
            for (int i = 0; i <= j; ++i) {	// i <= j
                dp[i][j] = (s[i] == s[j]) && 
                        (j - i < 2 || dp[i + 1][j - 1]);
                if (dp[i][j]) ++res;
            }
        }
        return res;
    }
};

// 131. Palindrome Partitioning

// 9. Palindrome Number
// Reverse integer function
class Solution {
public:
    bool isPalindrome(int x) {
        if (x < 0) return false;
        return (reverseInteger(x) == x);
    }
    int reverseInteger(int x) {
        int res = 0;
        while (x != 0) {
            if (abs(res) > INT_MAX / 10) return 0; // must check overflow
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }
};

// 125. Valid Palindrome
class Solution {
public:
    bool isPalindrome(string s) {
        int i = 0, j = s.size() - 1;
        while (i < j) {
            if (!isalnum(s[i])) ++i;
            else if (!isalnum(s[j])) --j;
            else if (tolower(s[i]) != tolower(s[j])) return false;
            else {++i; --j;}
        }
        return true;
    }
};

// ===== 4. hashmap, hashset ===
// 76. Minimum Window Substring
// Given a string S and a string T, find the minimum window in S 
// which will contain all the characters in T in complexity O(n).
class Solution {
public:
    string minWindow(string s, string t) {
        string res = "";
        int left = 0, cnt = 0, minleft = -1, minlen = INT_MAX; // left: left index of slide window
        // unordered_map<char, int> m; // method 1: using hashmap
        vector<int> m(128, 0); // method 2: 128/256 ASCII chars
        for (char c : t) ++m[c];
        for (int i = 0; i < s.size(); ++i) {
            if (--m[s[i]] >= 0) ++cnt;  // s[i] is in t
            while (cnt == t.size()) {  // shrink the window
                if (minlen > i - left + 1) { // cur window is smaller than previous one
                    minlen = i - left + 1;
                    // res = s.substr(left, minlen); // method 1: using hashmap
                    minleft = left; // method 2:
                    
                }
                if (++m[s[left]] > 0) --cnt; // shift window to right
                ++left;
            }
        }
        // return res;  // method 1: using hashmap
        return (minleft == -1) ? "" : s.substr(minleft, minlen); // method 2:
    }
};

// 325. Maximum Size Subarray Sum Equals k
// Find the maximum length of a contiuous subarray that sums to k
class Solution {
public:
    int maxSubArrayLen(vector<int>& nums, int k) {
        int res = 0, sum = 0;
        unordered_map<int, int> m; // sum[0:i]--i
        for (int i = 0; i < nums.size(); ++i) {
            sum += nums[i];
            if (sum == k) res = i + 1; // subarray[0:i] sum equals k
            else if (m.count(sum - k)) // subarray[j:i] sum equals k
                res = max(res, i - m[sum - k]);
            
            // to max subarray
            // add m[sum] only if no existed
            if (!m.count(sum)) m[sum] = i;
        }
        return res;
    }
};