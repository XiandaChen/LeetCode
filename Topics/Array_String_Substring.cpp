//157. Read N Characters Given Read4 - Call read() only
// Forward declaration of the read4 API.
int read4(char *buf);
class Solution {
public:
    int read(char *buf, int n) {
        char read4buf[4];
        int read4Cnt = 0, copyIndx = 0;
        for (int i = 0; i < n; ++i) {
            if (read4Cnt == copyIndx) {
                read4Cnt = read4(read4buf);
                copyIndx = 0;
                if (read4Cnt == 0) return i;
            }
            buf[i] = read4buf[copyIndx++];
        }
        return n;
    }
};

//158. Read N Characters Given Read4 II - Call multiple time
// Forward declaration of the read4 API.
int read4(char *buf);
class Solution {
public:
    int read(char *buf, int n) {
        for (int i = 0; i < n; ++i) {
            // chars previously read had been copyied to buf, read4() again
            if (readCnt == writeIndx) { 
                readCnt = read4(read4buf);
                writeIndx = 0; // reset to 0, must here
                if (readCnt == 0) return i; // end of file
                // writeIndx = 0; // error if here
            }
            buf[i] = read4buf[copyIndx++]; // copy from read4buf to buf
        }
        return n;
    }
private:
    // to hold chars everytime read from read4()
    char read4buf[4]; 
    // readCnt: actual num of chars by read4()
    // copyIndx: char indx being copied from read4buf to buf
    int readCnt = 0, copyIndx = 0; 
};

// 7. Reverse Integer
class Solution {
public:
    int reverse(int x) {
        int res = 0;
        while (x != 0) {
			// must check overflow if input x is larger than INT_MAX
            if (abs(res) > INT_MAX / 10) return 0;  
            res = res * 10 + x % 10;
            x /= 10;
        }
        return res;
    }
};

// 8. String to Integer (atoi)
class Solution {
public:
    int myAtoi(string str) {
        if (str.empty()) return 0;
        int sign = 1, base = 0, i = 0, n = str.size();
        while (i < n && str[i] == ' ') ++i;
        if (i < n && (str[i] == '+' || str[i] == '-')) {
            sign = (str[i++] == '+') ? 1 : -1;
        }
        while (i < n && str[i] >= '0' && str[i] <= '9') {
            // must check edge case: larger than INT_MAX
            if (base > INT_MAX / 10 || (base == INT_MAX / 10 && str[i] - '0' > 7)) {
                return (sign == 1) ? INT_MAX : INT_MIN;
            }
            base = 10 * base + (str[i++] - '0');
        }
        return base * sign;
    }
};

// 65 Validate number
// Validate if a given string can be interpreted as a decimal number.
class Solution {
public:
    bool isNumber(string s) {
        int len = s.size(), left = 0, right = len - 1;
        // eExisted: 'e/E' must be at most one time
        // dotExisted: '.' must be at most one time
        // digitExisted: at least one digit before 'e/E' if 'e/E' exists
        bool eExisted = false, dotExisted = false, digitExisted = false;
        
        // pre-process to remove space at the front and end
        while (s[left] == ' ') ++left;
        while (s[right] == ' ') --right;
        
        // process the first char: must be '.', digit,  or '+/-'
        if (s[left] == '.') dotExisted = true;
        else if ('0' <= s[left] && s[left] <= '9') digitExisted = true;
        else if (s[left] != '+' && s[left] != '-') return false; 
        
        // process chars in the middle
        for (int i = left + 1; i < right; ++i) {
            if ('0' <= s[i] && s[i] <= '9') digitExisted = true;
            else if (s[i] == 'e' || s[i] == 'E') {
                // 'e/E' must be at most one time
                // must have digit before 'e/E'
                // must be digit or '.' right before 'e/E'
                if (!eExisted && digitExisted && 
                    ('0' <= s[i - 1] && s[i - 1] <= '9' || s[i - 1] == '.'))
                    eExisted = true;
                else    return false;
            }
            else if (s[i] == '+' || s[i] == '-') {
                // '+/-' occur in the middle must be after 'e/E'
                if (s[i - 1] != 'e' && s[i - 1] != 'E') return false;
            }
            else if (s[i] == '.') {
                // '.' must be at most one time
                // '.' must not be after 'e/E'
                if (!dotExisted && !eExisted) dotExisted = true;
                else return false;
            }
            else return false;
        }
        
        // process the last char: must be digit or '.'
        if ('0' <= s[right] && s[right] <= '9') return true;
        else if (s[right] == '.' && !dotExisted && !eExisted && digitExisted) return true;
        else return false;
    }
};

// 71. Simplify Path
// Simplify an (Unix-style) absolute path for a file to the canonical path.
class Solution {
public:
    string simplifyPath(string path) {
        vector<string> v; // to hold substrs
        string res;
        // seperate string using '/' or '////..'
        int i = 0;
        while (i < path.size()) {
            while (path[i] == '/' && i < path.size()) ++i;
            if (i == path.size()) break; // must check
            int start = i;
            while (path[i] != '/' && i < path.size()) ++i;
            int end = i - 1;
            string ss = path.substr(start, end - start + 1);
            if (ss == "..") { 
                if (!v.empty()) v.pop_back();
            } // must use {} to seperate, otherwise "else if" match
            else if (ss != ".") v.push_back(ss);
        }
        if (v.empty()) return "/";
        for (int i = 0; i < v.size(); ++i) {
            res += '/' + v[i];
        }
        return res;
    }
};

// 76. Minimum Window Substring
// Find the minimum window in string S which contains string T in complexity O(n)
class Solution {
public:
    string minWindow(string s, string t) {
        string res = "";
        int left = 0, cnt = 0, minleft = -1, minlen = INT_MAX; // left: left index of slide window
        unordered_map<char, int> m; // method 1: using hashmap
        // vector<int> m(128, 0); // method 2: 128/256 ASCII chars
        for (char c : t) ++m[c];
        for (int i = 0; i < s.size(); ++i) {
            if (--m[s[i]] >= 0) ++cnt;  // s[i] is in t
            while (cnt == t.size()) {  // shrink the window
                if (minlen > i - left + 1) { // cur window is smaller than previous one
                    minlen = i - left + 1;
                    res = s.substr(left, minlen); // method 1: using hashmap
                    // minleft = left; // method 2:                
                }
                if (++m[s[left]] > 0) --cnt; // shift window to right
                ++left;
            }
        }
        return res;  // method 1: using hashmap
        // return (minleft == -1) ? "" : s.substr(minleft, minlen); // method 2:
    }
};

// 340. Longest Substring with At Most K Distinct Characters
// Find the length of the longest substring T that contains at most k distinct characters
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> m;
        int res = 0, left = 0; // left: left indx of the window
        for (int i = 0; i < s.size(); ++i) {
            ++m[s[i]];
            while (m.size() > k) { // size of map = num of distinct chars
                if (--m[s[left]] == 0) m.erase(s[left]); // // no char s[left]
                ++left; // move the window forward
            }
            res = max(res, i - left + 1);
        }
        return res;
    }
};

// 523. Continuous Subarray Sum, using accumulative sum
// Continuous subarray of size at least 2 that sums up to a multiple of k
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        for (int i = 0; i < nums.size(); ++i) {
            int sum = nums[i];
            // not need, since subarrar of size at least 2
            // if (k != 0 && sum % k == 0) return true; 
            for (int j = i + 1; j < nums.size(); ++j) {
                sum += nums[j];
                if (sum == k) return true;
                if (k != 0 && sum % k == 0) return true;
            }
        }
        return false;
    }
};

// 560. Subarray Sum Equals K, using accumulative sum
// Find the total number of continuous subarrays whose sum equals to k.
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, n = nums.size();
        vector<int> sums(n); // sums[i]: sum of 0..i
        sums[0] = nums[0];
        for (int i = 1; i < n; ++i) // sums
            sums[i] = sums[i - 1] + nums[i];
        for (int i = 0; i < n; ++i) { // check sums[j..i], j = 0..(i-1)
            if (sums[i] == k) ++res;
            for (int j = i - 1; j >= 0; --j) {
                if (sums[i] - sums[j] == k) ++res;
            }
        }
        return res;
    }
};
// 560. Subarray Sum Equals K, using Hashmap
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, sum = 0;
        unordered_map<int, int> m{{0, 1}}; // sum--count
        for (int i = 0 ; i < nums.size(); ++i) {
            sum += nums[i];
            res += m[sum - k]; // for sum, if [sum-k] exist, [k] exist
            ++m[sum];
        }
        return res;
    }
};

// 304. Range Sum Query 2D - Immutable
// The sum of the rectangle of upper left corner (row1, col1) and lower right corner (row2, col2)
class NumMatrix {
public:
    NumMatrix(vector<vector<int>>& matrix) {
        if (matrix.empty() || matrix[0].empty()) return;
        // add row fo 0, and col of 0 for dp[i][0] and dp[0][j]
        dp.resize(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));
        for (int i = 1; i <= matrix.size(); ++i) {
            for (int j = 1; j <= matrix[0].size(); ++j)
                dp[i][j] = dp[i][j - 1] + dp[i - 1][j] - dp[i - 1][j - 1] + matrix[i - 1][j - 1]; // not matrix[i][j]
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        // indx increase one, due to added row-0 and col-0 in dp[][]
        return dp[row2 + 1][col2 + 1] - dp[row2 + 1][col1] - dp[row1][col2 + 1] + dp[row1][col1];
    }
private:
    vector<vector<int>> dp;
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

// 825. Friends Of Appropriate Ages
class Solution {
public:
    int numFriendRequests(vector<int>& ages) {
        int res = 0, maxAge = 120;
        vector<int> ageCount(maxAge + 1, 0);
        for (int age : ages) ++ageCount[age];
        for (int A = 1; A <= maxAge; ++A) {
            for (int B = 0.5 * A + 7 + 1; B <= A; ++B)
                // must minus (A == B)
                res += ageCount[A] * (ageCount[B] - (A == B));
        }
        return res;
    }
};

// 161. One Edit Distance
// Insert/delete/replace a character into s to get t
class Solution {
public:
    bool isOneEditDistance(string s, string t) {
        if (s.size() < t.size()) swap(s, t); // guarantee s longer than t
        int m = s.size(), n = t.size(), diff = m - n;
        // case 1: if length diff > 1
        if (diff > 1) return false;
        else if (diff == 1) { // case 2: remove one char from longer s
            for (int i = 0; i < n; ++i) { // n, not m
                if (s[i] != t[i]) // s[i] should be removed
                    return s.substr(i + 1) == t.substr(i); // s[i+1, ..]=t[i..]
            }
        }
        else { // case 3: diff=0, only one replace
            int cnt = 0;
            for (int i = 0; i < m; ++i) 
                if (s[i] != t[i]) ++cnt;
            return cnt == 1;
        }
        return true;
    }
};