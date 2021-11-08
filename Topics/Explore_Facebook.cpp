// ===================== 1. Arrays and Strings =====================
// 3. Longest Substring Without Repeating Characters
// Given a string, find the length of the longest substring without repeating characters.
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> m; // char--last pos
        // left: left indx of last longest substring (window) w.o repeating
        int res = 0, left = -1; 
        
        for (int i = 0; i < s.size(); ++i) {
            // chararcter exist, and its last pos is larger that left indx
            if (m.count(s[i]) && left < m[s[i]]) left = m[s[i]];
            m[s[i]] = i;
            res = max(res, i - left);
        }
        
        return res;
    }
};

// 241. Different Ways to Add Parentheses
// DC
class Solution {
public:
    vector<int> diffWaysToCompute(string input) {
        if (input.empty()) return {};
        vector<int> res;
        for (int i = 0; i < input.size(); ++i) {    // divide and conquer at position i
            if (input[i] == '+' || input[i] == '-' || input[i] == '*') {
                vector<int> left = diffWaysToCompute(input.substr(0, i)); // calculate left substring
                vector<int> right = diffWaysToCompute(input.substr(i + 1)); // calculate right substring
                for (int j = 0; j < left.size(); ++j) {     // conquer
                    for (int k = 0; k < right.size(); ++k) {
                        if (input[i] == '+') res.push_back(left[j] + right[k]);
                        else if (input[i] == '-') res.push_back(left[j] - right[k]);
                        else res.push_back(left[j] * right[k]);
                    }
                }
            }
        }
        if (res.empty()) res.push_back(stoi(input));    // input only includes a number
        return res;
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

// 8. String to Integer (atoi)
// Implement atoi which converts a string to an integer.
class Solution {
public:
    int myAtoi(string str) {
        if (str.empty()) return 0;
        
        int sign = 1, num = 0, n = str.size();
        int i = 0;
        
        while (i < n && str[i] == ' ') ++i; // skip spaces in the front
        
        if (i < n && (str[i] == '+' || str[i] == '-')) {
            sign = (str[i] == '+') ? 1 : -1; // sign simbol
            ++i;
        }
        
        while (i < n && '0' <= str[i]  && str[i] <= '9') {
            // corner case: larger than INT_MAX
            if (num > INT_MAX / 10 || (num == INT_MAX / 10 && str[i] - '0' > 7))
                return (sign == 1) ? INT_MAX : INT_MIN;
            num = num * 10 + (str[i] - '0'); // or, num = num * 10 + (str[i++] - '0');
            ++i;
        }
        
        return sign * num;
    }
};

// 65. Valid Number
// Validate if a given string can be interpreted as a decimal number.
class Solution {
public:
    bool isNumber(string s) {
        // eExisted: 'e/E' must appear at most one time
        // dotExisted: '.' must appear at most one time, and appear before 'e/E'
        // digitExisted: at least one digit exists before 'e/E' if 'e/E' exists
        // signExisted: '+/-' must be at the begining, or right after 'e/E' simbol 
        bool eExisted = false, dotExisted = false, digitExisted = false, signExisted = false;
        int left = 0, right = s.size() - 1;
        
        // remove spaces in the front and the end
        while (s[left] == ' ') ++left;
        while (s[right] == ' ') --right;
        
        // the first character must be: digit, '.', or '+/-'
        if ('0' <= s[left] && s[left] <= '9') digitExisted = true;
        else if (s[left] == '.') dotExisted = true;
        else if (s[left] == '+' || s[left] == '-') signExisted = true;
        else return false;
        
        // the characters in the middle
        for (int i = left + 1; i < right; ++i) {
            if ('0' <= s[i] && s[i] <= '9') digitExisted = true;
            else if (s[i] == 'e' || s[i] == 'E') {
                // 'e/E' has not appeared yet
                // digit appeared before 'e/E' simbol
                // the character right before 'e/E' must be digit or '.'
                if (!eExisted && digitExisted && ('0' <= s[i - 1] && s[i - 1] <= '9' || s[i - 1] == '.'))
                    eExisted = true;
                else return false;
            }
            else if (s[i] == '.') {
                // at most one '.' simbol, and must appear before 'e/E'
                if (!dotExisted && !eExisted) dotExisted = true;
                else return false;
            }
            else if (s[i] == '+' || s[i] == '-') {
                // '+/-' in the middle must be right after 'e/E' simbol
                if (s[i - 1] != 'e' && s[i - 1] != 'E') return false;
            }
            else { // for other charactrers: input=". 1"
                return false;
            }
        }
        
        // the last character must be: digit, '.'
        if ('0' <= s[right] && s[right] <= '9') return true;
        // else if (s[right] == '.') return true; // error for case: input="."
        else if (s[right] == '.' && !dotExisted && !eExisted && digitExisted) return true;
        else return false;
    }
};

// 13. Roman to Integer
// Given a roman numeral, convert it to an integer.
// Input: "MCMXCIV";  Output: (+1000 (-100 +1000) (-10 +100) (-1 +5)) = 1994
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

// 15. 3Sum
// Find all unique triplets (a, b, c) in the array which gives the sum of zero
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end()); // sort increasing
		// nums is empty, or nums are all larger/smaller than zero
        if (nums.empty() || nums.front() > 0 || nums.back() < 0) return {};
		vector<vector<int>> res;
        
        for (int i = 0; i < (int)nums.size() - 2; ++i) { // '-2'
            if (nums[i] > 0) break; // numbers at pos i and later are larger than zero
            if (i > 0 && nums[i] == nums[i - 1]) continue;  // remove duplicate triplets
            
			// towsum problem: two pointers
            int j = i + 1, k = (int)nums.size() - 1, twosum = 0 - nums[i];
            while (j < k) {
                if (nums[j] + nums[k] == twosum) { // found
                    res.push_back({nums[i], nums[j], nums[k]}); // {a, b, c}
                    while(j < k && nums[j] == nums[j + 1]) ++j;   // remove duplicate triplets
                    while(j < k && nums[k] == nums[k - 1]) --k;   // remove duplicate triplets
                    ++j; --k;
                }
                else if (nums[j] + nums[k] < twosum) j++;
                else k--;
            }
        }
        return res;
    }
};

// 26. Remove Duplicates from Sorted Array
class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int pre = 0, cur = 0, n = nums.size();
        while (cur < n) {
            // move cur forward when encountering duplicate num
            if (nums[pre] == nums[cur]) ++cur;
            else nums[++pre] = nums[cur++]; // increment pre
        }
        return pre + 1;
    }
};
// 83. Remove Duplicates from Sorted List
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode * cur = head;
        while (cur && cur->next) {
            if (cur->val == cur->next->val) 
                cur->next = cur->next->next;
            else
                cur = cur->next;
        }
        return head;
    }
};

// 31. Next Permutation
//  Q46, Q47
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // 1,2,7,4,3,1 => 1,3,7,4,2,1 => 1,3,1,2,4,7
        int n = nums.size(), i = n - 2, j = n - 1;
        
        // non-increasing portion from the end
        while (i >= 0 && nums[i] >= nums[i + 1]) --i; // nums[i] = 2
        
        if (i >= 0) { // check otherwise input nums is largest permutation
            while (j >= 0 && nums[j] <= nums[i]) --j; // nums[j] = 3
            swap(nums[i], nums[j]);
        }
        
        reverse(nums.begin() + i + 1, nums.end());
    }
};

// 43. Multiply Strings
// Given two non-negative integers as strings, return the product as a string.
class Solution {
public:
    string multiply(string num1, string num2) {
        int m = num1.size(), n = num2.size();
        vector<int> vals(m + n); // length of multiply val is not larger than m+n
        string res = "";
        for (int i = m - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int mul = (num1[i] - '0') * (num2[j] - '0');
                int highpos = i + j, lowpos = i + j + 1, sum = mul + vals[lowpos]; // previous vals[lowpos] 
                vals[highpos] += sum / 10; // carry
                vals[lowpos] = sum % 10; // remainder
            }
        }
        // add vals in string from high position to low position
        for (int val : vals) {
            // 'val != 0': skip leading zeros
            if (!res.empty() || val != 0) res.push_back(val + '0');
        }
        // return res; // eror for corner case: input="0"
        return res.empty() ? "0" : res; 
    }
};

// 438. Find All Anagrams in a String
// Find all the start indices of p's anagrams in string s.
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.empty()) return {};
        vector<int> res, ts(128, 0), tp(128, 0); // vector for operator "=="
        
        // sliding window of p.size()
        for (int i = 0; i < p.size(); ++i) {
            ++ts[s[i]]; ++tp[p[i]];
        }
        // two table match, and save indx 0
        if (tp == ts) res.push_back(0);
        
        // check for the rest of s
        for (int i = p.size(); i < s.size(); ++i) {
            --ts[s[i - p.size()]]; // remove leftmost char from the window
            ++ts[s[i]]; // move window right by one char
            if (tp == ts) res.push_back(i - p.size() + 1);
        }
        
        return res;
    }
};
// 49. Group anagrams
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

// 67. Add Binary
// Given two binary strings, return their sum (also a binary string).
class Solution {
public:
    string addBinary(string a, string b) {
        string res = "";
        int i = a.size() - 1, j = b.size() - 1, carry = 0;
        while (i >= 0 || j >= 0) {
            int ta = (i >= 0) ? a[i--] - '0' : 0;  // not forget i--
            int tb = (j >= 0) ? b[j--] - '0' : 0;  // not forget j--
            int sum = ta + tb + carry; // carry is from last calculation
            res.insert(res.begin(), (sum % 2) + '0'); // value for cur pos
            carry = sum / 2; // carry for next calculation
        }
        // return res; // error, corner case: last calculation has carry=1
        return (carry == 1) ? '1' + res : res;
    }
};

// 76. Minimum Window Substring
// Find the minimum window in S which contains all the characters in T in complexity O(n)
class Solution {
public:
    string minWindow(string s, string t) {
        string res  = "";
        unordered_map<char, int> m; // char-num for t
        int left = 0, cnt = 0, minlen = INT_MAX;
        for (char c : t) ++m[c];
        for (int i = 0; i < s.size(); ++i) {
            // if (--m[s[i]] > 0) ++cnt; // error
            if (--m[s[i]] >= 0) ++cnt; // s[i] is in t, increase cnt
            while (cnt == t.size()) { // window containing t is found
                if (i - left + 1 < minlen) { // cur window is smaller
                    minlen = i - left + 1;
                    res = s.substr(left, minlen);
                }
                if (++m[s[left]] > 0) --cnt; // shift window to right by one char
                ++left;
            }
        }
        return res;
    }
};

// 88. Merge Sorted Array
class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m - 1, j = n - 1, k = m + n - 1;
        while (i >= 0 && j >= 0) {
            // move the larger one to the end of nums1, i.e., nums1[k]
            if (nums1[i] > nums2[j]) nums1[k--] = nums1[i--];
            else nums1[k--] = nums2[j--];
        }
        // if nums2 have elements left
        while (j >= 0) nums1[k--] = nums2[j--];
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
// 680. Valid Palindrome II
// Judge whether you can make it a palindrome by deleting at most one character.
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) // if diff, remvoe one character
                return isPalindrome(s, left, right - 1) || isPalindrome(s, left + 1, right);
            ++left; --right;
        }
        return true;
    }
    bool isPalindrome(string s, int left, int right) {
        while (left < right) {
            if (s[left] != s[right]) return false;
            ++left; --right;
        }
        return true;
    }
};

// 157. Read N Characters Given Read4 - only call read() once
int read4(char *buf);
class Solution {
public:
    int read(char *buf, int n) {
        char read4buf[4];
        int read4Cnt = 0, copyIndx = 0;
        for (int i = 0; i < n; ++i) {
            // character previously read4() have been move to buf
            if (copyIndx == read4Cnt) { // read4() new characters
                read4Cnt = read4(read4buf);
				copyIndx = 0; // initial copyIndx
                if (read4Cnt == 0) return i;
                // copyIndx = 0; // ok here, initial copyIndx
            }
            buf[i] = read4buf[copyIndx++];
        }
        return n;
    }
};
// 158. Read N Characters Given Read4 - call read() multiple times
int read4(char *buf);
class Solution {
public:
    int read(char *buf, int n) {
        for (int i = 0; i < n; ++i) {
            // chars previously read had been copyied to buf, read4() again
            if (copyIndx == read4Cnt) {
                read4Cnt = read4(read4buf);
                copyIndx = 0; // every read(), must initial copyIndx=0
                if (read4Cnt == 0) return i;
                // writeIndx = 0; // error if here
            }
            buf[i] = read4buf[copyIndx++];
        }
        return n;
    }
private:
    // hold chars everytime read from read4()
    char read4buf[4];
    // read4Cnt: actual num of chars read from read4()
    // copyIndx: char indx being copied from read4buf to buf
    int read4Cnt = 0, copyIndx = 0;
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

// 238. Product of Array Except Self
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> fwd(n, 1), bck(n, 1), res(n, 0);
        for (int i = 1; i < n; ++i) // fwd[0] = 1
            fwd[i] = fwd[i - 1] * nums[i - 1];
        for (int i = n - 2; i >= 0; --i) // bck[n-1] = 1
            bck[i] = bck[i + 1] * nums[i + 1];
        for (int i = 0; i < n; ++i)
            res[i] = fwd[i] * bck[i];
        return res;
    }
};
// Constant space complexity
class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size(), back = 1;
        vector<int> res(n, 1);
        for (int i = 1; i < n; ++i)
            res[i] = res[i - 1] * nums[i - 1]; // fwd(n, 1)
        for (int i = n - 1; i >= 0; --i) {
            res[i] *= back; // res[i] = fwd[i] * bck[i]
            back *= nums[i]; // bck[i] = bck[i+1] * nums[i+1]
        }
        return res;
    }
};

//273. Integer to English Words
class Solution {
public:
    string numberToWords(int num) {
        vector<string> v = {"Thousand", "Million", "Billion"};
        string res = process3digit(num % 1000); // process the last three digit
        for (int i = 0; i < 3; ++i) { // INT_MAX: billion, three more 3-digit parts
            num /= 1000; // remove last three digit
            res = num % 1000 ? process3digit(num % 1000) + " " + v[i] + " " + res : res;
        }
        // remove spaces at the end
        while (res.back() == ' ') res.pop_back();
        // check zero
        return res.empty() ? "Zero" : res;
    }
    string process3digit(int num) { // helper func to process less-than thousand
        vector<string> v1 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
                            "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", 
                            "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
        vector<string> v2 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
        string res;
        int a = num / 100, b = num % 100, c = num % 10; // a: hundreds, b:tens, c: ones
        // get from v1 if less than twenty, otherwise we need v2
        res = b < 20 ? v1[b] : v2[b / 10] + (c ? " " + v1[c] : ""); // for >= 20, check c
        if (a > 0)
            res = v1[a] + " Hundred" + (b ? " " + res : ""); // check b
        return res;
    }
};

// 283. Move zeros
// move all 0's to the end while maintaining the relative order of the non-zero elements 
class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        for (int i = 0, j = 0; i < nums.size(); ++i) {
            // pointer i for iterating the array, 
            // pointer j just works on non-zero elements
            if (nums[i]) swap(nums[i], nums[j++]);
        }
    }
};

// 340. Longest Substring with At Most K Distinct Characters
class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        unordered_map<char, int> m; // char-num
        int res = 0, left = 0; // left: left indx of substring window
        for (int i = 0; i < s.size(); ++i) {
            ++m[s[i]];
            while (m.size() > k) {// sizeofmap=#distinct chars > k
                if (--m[s[left]] == 0) m.erase(s[left]); // no char s[left]
                ++left; // move the window forward
            }
            res = max(res, i - left + 1); // update lenght
        }
        return res;
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

// 468. Validate IP Address
class Solution {
public:
    string validIPAddress(string IP) {
        istringstream iss(IP);
        string t = ""; // to store substring b/w '.' (or ':')
        int cnt  = 0; // IPv4: cnt=4; IPv6: cnt=6
        if (IP.find(':') == string::npos) { // not found ':', is IPv4
            while (getline(iss, t, '.')) { // get string seperate by '.'
                ++cnt;
                if (cnt > 4 || t.empty() || t.size() > 3 || (t.size() > 1 && t[0] == '0'))
                    return "Neither";
                for (char c : t)
                    if (c < '0' || '9' < c) return "Neither";
                if(stoi(t) < 0 || 255 < stoi(t)) return "Neither"; // is stoi(), not atoi()
            }
            // check if last char is '.'
            return (cnt == 4 && IP.back() != '.') ? "IPv4" : "Neither";
        }
        else { // IPv6
            while (getline(iss, t, ':')) {
                ++cnt;
                if (cnt > 8 || t.empty() || t.size() > 4) return "Neither";
                for (char c : t)
                    if (!('0' <= c && c <= '9') && !('a' <= c && c <= 'f')
                       && !('A' <= c && c <= 'F')) return "Neither";
            }
            // check if last char is ':'
            return (cnt == 8 && IP.back() != ':') ? "IPv6" : "Neither";
        }
    }
};

// 560. Subarray Sum Equals K
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        int res = 0, n = nums.size();
        vector<int> sums(n); // sums[i]: sum of 0..i
        sums[0] = nums[0];
        for (int i = 1; i < n; ++i)
            sums[i] = sums[i - 1] + nums[i];
        for (int i = 0; i < n; ++i) {
            if (sums[i] == k) ++res; // not forget sums[0..i]
            for (int j = i - 1; j >= 0; --j) // check sums[j..i], j = 0..(i-1)
                if (sums[i] - sums[j] == k) ++res;
        }
        return res;
    }
};


// ===================== 2. Linked List =====================
// 2. Add Two Numbers
// Two non-empty linked lists representing two non-negative integers (in reverse order)
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode * dummy = new ListNode(0); // dummy to simplify the code
        ListNode * p = l1, * q = l2, * cur = dummy;
        int carry = 0;
        while (p != NULL || q != NULL) {
            int x = (p != NULL) ? p->val : 0;
            int y = (q != NULL) ? q->val : 0;
            int z = (x + y + carry) % 10; // cur->val
            carry = (x + y + carry) / 10;
            cur->next = new ListNode(z); // add new node
            cur = cur->next;             // set current cursor
            p = (p != NULL) ? p->next : NULL;
            q = (q != NULL) ? q->next : NULL;
        }
        if  (carry > 0) // extra carry at the end
            cur->next = new ListNode(carry);
        return dummy->next; 
    }
};
// 445. Add Two Numbers II: The most significant digit comes first
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int> s1, s2;
        while (l1) {
            s1.push(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            s2.push(l2->val);
            l2 = l2->next;
        }
        int sum = 0;
        ListNode * res = new ListNode(0);
        while (!s1.empty() || !s2.empty()) {
            if (!s1.empty()) {sum += s1.top(); s1.pop();}
            if (!s2.empty()) {sum += s2.top(); s2.pop();}
            res->val = sum % 10; // cur value
            ListNode * head = new ListNode(sum / 10); // carry
            head->next = res; // linking
            res = head;
            sum /= 10; // carry for higher unit
        }
        // check if highest carry equals to zero
        return res->val == 0 ? res->next : res;
    }
};

// 21. Merge Two Sorted Lists
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (!l1) return l2;
        if (!l2) return l1;
        if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};

// 138. Copy List with Random Pointer, 
// deep copy (see Clone Graph), unordered_map<Node*, Node*> m; // oldnode--newnode
// Node(int _val, Node* _next, Node* _random)
class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (!head) return nullptr;
        unordered_map<Node*, Node*> m; // oldnode--newnode
        Node * res = new Node (head->val, nullptr, nullptr);
        Node * oldNode = head->next, * newNode = res;
        m[head] = res;
        while (oldNode) { // copy nodes, and consturct map for random ptr
            Node * t = new Node(oldNode->val, nullptr, nullptr);
            newNode->next = t;
            m[oldNode] = t;
            oldNode = oldNode->next;
            newNode = newNode->next;
        }
        oldNode = head; newNode = res;
        while (oldNode) { // precess random ptr
            newNode->random = m[oldNode->random];
            oldNode = oldNode->next;
            newNode = newNode->next;
        }
        return res;
    }
};

// 143. Reorder List
// Given 1->2->3->4->5, reorder it to 1->5->2->4->3.
class Solution {
public:
    void reorderList(ListNode* head) {
        if (!head || !head->next || !head->next->next) return;
        ListNode * slow = head, * fast = head;
        while (fast->next && fast->next->next) { // step 1: find mid
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode * mid = slow->next; // mid node
        slow->next = NULL; // divide the list
        // step 2: reverse the second part
        ListNode * last = mid, * pre = NULL;
        while (last) {
            ListNode * tmp = last->next; // save last->next
            last->next = pre;
            pre = last; // when finishing, pre points to the last node
            last = tmp;
        }
        // step 3: add element of second part to first part
        while (head && pre) {
            ListNode * tmp = head->next; // save head->next
            head->next = pre;
            pre = pre->next;
            head->next->next = tmp; // link newnode to oldlist
            head = tmp; // move head to oldhead->next
        }
    }
};

// ===================== Tree and Graph =====================
// 98. Validate Binary Search Tree
// Recursion
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        // long to cover int edge case: 2147483647
        return isValidBST(root, LONG_MIN, LONG_MAX); 
    }
    bool isValidBST(TreeNode * node, long mn, long mx) {
        if (!node) return true;
        if (node->val <= mn || node->val >= mx) return false;
        return isValidBST(node->left, mn, node->val) 
            && isValidBST(node->right, node->val, mx);
    }
};
// Stack: inorder traversal
class Solution {
public:
    bool isValidBST(TreeNode* root) {
        if (!root) return true;
        stack<TreeNode*> st;
        TreeNode * p = root, * pre = NULL;
        while (p || !st.empty()) { // inorder traversal
            while (p) { // left
                st.push(p);
                p = p->left;
            }
            p = st.top(); st.pop(); // mid
            if (pre && p->val <= pre->val) return false; // logic, <==
            pre = p;
            p = p->right; // right
        }
        return true;
    }
};

// 114. Flatten Binary Tree to Linked List
class Solution {
public:
    void flatten(TreeNode* root) {
        TreeNode * cur = root;
        while (cur) {
            if (cur->left) {
                TreeNode * tmp = cur->left;
                while (tmp->right) // right-most child of cur->left
                    tmp = tmp->right; 
                tmp->right = cur->right;
                cur->right = cur->left;
                cur->left = NULL; // must
            }
            cur = cur->right;
        }
    }
};

// 124. Binary Tree Maximum Path Sum
// Given a non-empty binary tree, find the maximum path sum.
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        dfs(root, res);
        return res;
    }
    // maxsum of path from cur node to a leaf 
    int dfs (TreeNode * node, int & res) {
        if (!node) return 0;
        // maxsum of node->left
        int left = max(dfs(node->left, res), 0);  // consider the path only if sum>=0
        int right = max(dfs(node->right, res), 0); // right
        res = max(res, left + right + node->val);
        return max(left, right) + node->val; // one path: only max(left, right)
    }
};

// 543. Diameter of Binary Tree
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int res = 0;
        dfs(root, res);
        return res;
    }
    // return lenght of longest path from node to a leaf
    int dfs(TreeNode* node, int & res) {
        if (!node) return 0;
        int left = dfs(node->left, res);
        int right = dfs(node->right, res);
        res = max(res, left + right);
        return max(left, right) + 1;
    }
};

// 133. Clone Graph
class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return NULL;
        unordered_map<Node*, Node*> m; // orignode-clonenode
        Node * clone = new Node(node->val);
        m[node] = clone;
        queue<Node*> q{{node}}; // BFS graph traversal
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                Node * t = q.front(); q.pop();
                for (auto neighbor : t->neighbors) {
                    if (!m.count(neighbor)) {
                        m[neighbor] = new Node(neighbor->val); // clone neighbor
                        q.push(neighbor); // add orig neighbor to queue
                    }
                    //add neighbor of cloned node
					// vector<Node*> neighbors;
                    m[t]->neighbors.push_back(m[neighbor]);
                }
            }
        }
        return clone;
    }
};

// 199. Binary Tree Right Side View
// ref. Q102, level order traversal
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        queue<TreeNode*> q{{root}}; // level order traversal
        while (!q.empty()) {
            // add the value of right-most node in last level
            res.push_back(q.back()->val);
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop(); // queue-front, stack-top
                if (t->left) q.push(t->left); // first
                if (t->right) q.push(t->right); // last
            }
        }
        return res;
    }
};

// 200. Number of Islands, DFS
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        vector<vector<bool>> visited(m, vector<bool>(n)); 
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                // skip if grid[i][j]=0, or had been visited
                if (grid[i][j] == '0' || visited[i][j]) continue;
                dfs(grid, i, j, visited);
                ++res;
            }
        }
        return res;
    }
    void dfs(vector<vector<char>> & grid, int i, int j, vector<vector<bool>> & visited) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() 
           || grid[i][j] == '0' || visited[i][j]) return;
        visited[i][j] = true;
        dfs(grid, i + 1, j, visited);
        dfs(grid, i - 1, j, visited);
        dfs(grid, i, j + 1, visited);
        dfs(grid, i, j - 1, visited);
    }
};

// 236. Lowest Common Ancestor of a Binary Tree, Recursion
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || p == root || q == root) return root;
        TreeNode * left = lowestCommonAncestor(root->left, p, q);
        TreeNode * right = lowestCommonAncestor(root->right, p, q);
        // if ancestor for p/q in root->left (root->right)
        if (left && right) return root;
        // // common ancestor for p&q in only left(or right)
        return left ? left : right;
    }
};

// 257. Binary Tree Paths, DFS
class Solution {
public:
    vector<string> binaryTreePaths(TreeNode* root) {
        if (!root) return {};
        vector<string> res;
        dfs(root, "", res);
        return res;
    }
    void dfs(TreeNode * node, string out, vector<string> & res) {
        if (!node->left && !node->right) 
            res.push_back(out + to_string(node->val));
        if (node->left) 
            dfs(node->left, out + to_string(node->val) + "->", res);
        if (node->right)
            dfs(node->right, out + to_string(node->val) + "->", res);
    }
};

// 

// 112. Path Sum, DFS
// Determine if the tree has a root-to-leaf path that sum equals to given value
class Solution {
public:
    bool hasPathSum(TreeNode* root, int sum) {
        if (!root) return false;
        // found a path to a leaf, and nodeVal==remainingSum
        if (!root->left && !root->right && root->val == sum) return true;
        return hasPathSum(root->left, sum - root->val) 
            || hasPathSum(root->right, sum - root->val);
    }
};
// 113. Path Sum II, DFS, find all root-to-leaf path sum equals to given value
class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        if (!root) return {};
        vector<vector<int>> res;
        vector<int> out;
        dfs(root, sum, out, res);
        return res;
    }
    void dfs(TreeNode * node, int sum, vector<int> & out, vector<vector<int>> & res) {
        if (!node) return;
        out.push_back(node->val); // must
        if (!node->left && !node->right && node->val == sum)
            res.push_back(out);
        if (node->left)
            dfs(node->left, sum - node->val, out, res);
        if (node->right)
            dfs(node->right, sum - node->val, out, res);
        out.pop_back(); // must
    }
};

// 269. Alien Dictionary, Graph BFS
class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_set<char> chars; // store all chars in given words
        set<pair<char, char>> s; // store order pairs
        vector<int> indegree(128, 0); // here assume first 128 ASCII
        queue<char> q; //hold zero-indegree node, and BFS traverse the graph
        string res = "";
        // get all chars in given words
        for (string w : words) chars.insert(w.begin(), w.end());
        // find all order pairs
        for (int i = 0; i < words.size() - 1; ++i) {
            int mn = min(words[i].size(), words[i + 1].size());
            for (int j = 0; j < mn; ++j) {
                // diff chars b/w two near words
                if (words[i][j] != words[i + 1][j]) {
                    s.insert({words[i][j], words[i + 1][j]});
                    break; // dont forget
                }
            }
        }
        // indegree for chars
        for (auto a : s) {
            ++indegree[a.second];
        }
        // add chars of indegree=zero to queue, that is traversed first
        for (char c : chars) {
            if (indegree[c] == 0) {
                q.push(c);
                res += c;
            }
        }
        // BFS traverse the graph from zero-indegree char
        while (!q.empty()) {
            char c = q.front(); q.pop();
            for (auto a : s) {
                if (c == a.first) {
                    if (--indegree[a.second] == 0) {
                        q.push(a.second);
                        res += a.second;
                    }
                }
            }
        }
        return res.size() == chars.size() ? res : "";
    }
};

// 426. Convert Binary Search Tree to Sorted Doubly Linked List
class Solution {
public:
    Node* treeToDoublyList(Node* root) {
        if (!root) return NULL;
        // head: left-most node; pre: pre-accessed node
        Node * head = NULL, * pre = NULL;
        dfs_inorder(root, head, pre);
        head->left = pre;  // doubly-liked list
        pre->right = head;
        return head;
    }
    void dfs_inorder(Node * node, Node *& head, Node *& pre) {
        // binary tree inorder traversal
        if (!node) return;
        // step 1: left  
        dfs_inorder(node->left, head, pre);
        // step 2: node in mid
        if (!head) { // left-most node
            head = node;
            pre = node;
        }
        else {
            pre->right = node;
            node->left = pre;
            pre = node;
        }
        // step3: right
        dfs_inorder(node->right, head, pre);
    }
};

// 785. Is Graph Bipartite? DFS
class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        // 0: not accessed, -1/1: diff colors
        vector<int> colors(graph.size(), 0);
        for (int i = 0; i < graph.size(); ++i) { // traverse all nodes
            if (colors[i] == 0 && !isValid(graph, colors, i, 1)) return false;
        }
        return true;
    }
    bool isValid(vector<vector<int>>& graph, vector<int> & colors, int i, int color) {
        // node cur had been colored, with valid color
        if (colors[i] != 0) return colors[i] == color;
        colors[i] = color;
        for (int neighbor : graph[i]) { // color neighbors with diff color
            if (!isValid(graph, colors, neighbor, -1 * color)) return false;
        }
        return true;
    }
};

// 314. Binary Tree Vertical Order Traversal, BFS
// Given a binary tree, return the  vertical order  traversal of its nodes' values. 
// (ie, from top to bottom, column by column).
// If two nodes are in the same row and column, the order should be from left to right.
// Input: [3,9,8,4,0,1,7,null,null,null,2,5]
// Ouput: [[4], [9,5], [3,0,1], [8,2], [7]]
class Solution {
public:
    vector<vector<int>> verticalOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> res;
        // root order: 0; left: -1; right: +1
        map<int, vector<int>> m; // vertical order--nodes
        queue<pair<int, TreeNode*>> q;  // order-node*
        q.push({0, root});
        
        // level order traversal
        while (!q.empty()) {
            auto a = q.front(); q.pop();
            m[a.first].push_back(a.second->val);
            if (a.second->left) q.push({a.first - 1, a.second->left});
            if (a.second->right) q.push({a.first + 1, a.second->right});
        }
        
        for (auto a : m) res.push_back(a.second);
        
        return res;
    }
};


// 987. Vertical Order Traversal of a Binary Tree, DFS
// If two nodes have the same position, then the smaller onve is reported first
// For each node at (X, Y), its left and right children: (X-1, Y-1) and (X+1, Y-1)
// Input: [3,9,20,null,null,15,7];    Output: [[9],[3,15],[20],[7]]
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (!root) return {};
        map<int, vector<pair<int, int>>> m; // x-[<y, val>..]
        dfs(root, 0, 0, m); // node map
        vector<vector<int>> res;
        for (auto a : m) {
            vector<int> col;
            sort(a.second.begin(), a.second.end()); // sort vector using y's
            for (int i = 0; i < a.second.size(); ++i)
                col.push_back(a.second[i].second);
            res.push_back(col);
        }
        return res;
    }
    void dfs(TreeNode * node, int x, int y, map<int, vector<pair<int, int>>> & m) {
        if (!node) return;
        // by default, sort() in increasing order, need to use "-y" to sort decreasing
        m[x].push_back(make_pair(-y, node->val)); 
        dfs(node->left, x - 1, y - 1, m);
        dfs(node->right, x + 1, y - 1, m);
    }
};
