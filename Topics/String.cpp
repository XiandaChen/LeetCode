// 91. Decode Ways
// Input: s = "226", Output: 3
// Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).
class Solution {
// recursion and memoization: Time O(n), Space O(n)
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        unordered_map<int, int> m; // <indx, ways> for string s[indx, end]
        return ways(s, 0, m);
    }
    // num of ways to decode string s[indx, end]
    int ways (const string &s, int indx, unordered_map<int, int> &m) {
        if (s[indx] == '0') return 0;  // condition 1: s[indx] != '0', must check first
        if (indx >= s.size() - 1) return 1;  // single digit or empty
        if (m.count(indx)) return m[indx];
        
        int w = ways(s, indx + 1, m);  // # ways of s[indx+1, end]
        
        int prefix = (s[indx] - '0') * 10 + (s[indx + 1] - '0');
        if (10 <= prefix && prefix <= 26)  // condition 2: 10 <= s[indx, indx+1] <= 26
            w += ways(s, indx + 2, m);
        
        m[indx] = w;
        return w;
    }
};
class Solution {
// DP: Time O(n), Space O(1)
public:
    int numDecodings(string s) {
        if (s.empty() || s[0] == '0') return 0;
        // vector<int> dp(s.size() + 1, 0); // not used, otherwise Space O(n)
        
        int w1 = 1, w2 = 1; // i = 0, dp[i-1]=1, dp[i-2]=1
        for (int i = 1; i < (int)s.size(); ++i) { // start from i=1
            int w = 0; // ways to decode string s[0, i]
            if (!isValid(s[i]) && !isValid(s[i - 1], s[i])) w = 0;
            if (isValid(s[i])) w = w1;
            if (isValid(s[i - 1], s[i])) w += w2;
            
            w2 = w1;
            w1 = w;
        }
        
        return w1;
    }
    bool isValid(const char c) {return c != '0';}
    bool isValid(const char c1, const char c2) {
        int num = (c1 - '0') * 10 + (c2 - '0');
        return (10 <= num) && (num <= 26);
    }
};

// 68. Text Justification
// Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
// Output: ["This    is    an", "example  of text", "justification.  "]
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> res;
        int index = 0, n = words.size();
        
        while (index < n) {
            // step 1: decide #words in the same line
            int totalChars = words[index].size(), last = index + 1;
            while (last < n && totalChars + words[last].size() + 1 <= maxWidth) {
                totalChars += 1 + words[last].size();  // 1 for ' ' before words[last]
                ++last; // when break, last is startIdx for next line
            }
            
            // step 2: construct the line
            string line;
            int gaps = last - index - 1; 
            // last line, or line with only one word
            // last line: left justified and no extra space is inserted b/w words.
            if (last == n || gaps == 0) { 
                for (int i = index; i < last - 1; ++i) {
                    line.append(words[i]);
                    line.append(" "); // " ", not ' '
                }
                line.append(words[last - 1]); // last word in the line
                if (line.size() < maxWidth) { // padding spaces at the end
                    line.append(maxWidth - line.size(), ' '); 
                }
            }
            else {  
                // no-last line: extra spaces are evenly distributed b/w words
                // # of extra spaces = (maxWidth - totalChars) / gaps
                int spaces = (maxWidth - totalChars) / gaps;
                int remain = (maxWidth - totalChars) % gaps;
                for (int i = index; i < last - 1; ++i) {
                    line.append(words[i]);
                    line.append(" ");
                    
                    // padding extra spaces b/w words
                    line.append(spaces, ' ');
                    if (i - index < remain) { // if not even, the left will be assigned more spaces
                        line.append(" "); 
                    }
                }
                line.append(words[last - 1]); // last word in the line
            }
            
            res.push_back(line);
            index = last;
        }
        
        return res;
    }
};

// 3. Longest Substring Without Repeating Characters
class Solution {
// Hashmap, sliding window: Time O(n), Space O(128)
public:
    int lengthOfLongestSubstring(string s) {
        vector<int> m(128, -1);  // char - most occur indx
        int res = 0, left = -1;
        for (int i = 0; i < (int)s.size(); ++i) {
            left = max(left, m[s[i]]);
            res = max(res, i - left);
            m[s[i]] = i;
        }
        return res;
    }
};

// 273. Integer to English Words
// Input: num = 1234567; Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven"
class Solution {
// Time: O(logn), Space: O(logn)
public:
    vector<string> UNDER20 = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight",
                            "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", 
                            "Sixteen", "Seventeen", "Eighteen", "Nineteen"};
    vector<string> UNDER100 = {"", "", "Twenty", "Thirty", "Forty", "Fifty", 
                               "Sixty", "Seventy", "Eighty", "Ninety"};
    vector<string> HTMB = {"Hundred" ,"Thousand", "Million", "Billion"};
    vector<int> BASE = {100, 1000, 1000*1000, 1000*1000*1000};  // process 3 digits
    
    string numberToWords(int num) {
        if (num == 0) return "Zero";
        return convert(num).substr(1); // remove " " at the begining
    }
    
    string convert(int num) {
        if (num == 0) return "";
        else if (num < 20) {
            return " " + UNDER20[num];  // add " "
        }
        else if (num < 100) {
            return " " + UNDER100[num / 10] + convert(num % 10);
        }
        else if (num >= 100) {
            for (int i = 3; i >= 0; --i) {
                if (num >= BASE[i])
                    return convert(num / BASE[i]) + " " + HTMB[i] + convert(num % BASE[i]);  
            }
        }
        
        return "";
    }
};

// 415. Add Strings
class Solution {
public:
    string addStrings(string num1, string num2) {
        string res = "";
        int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
        while (i >= 0 || j >= 0) {
            int a = (i >= 0) ? num1[i--] - '0' : 0;
            int b = (j >= 0) ? num2[j--] - '0' : 0;
            res.insert(res.begin(), (a + b + carry) % 10 + '0');
            carry = (a + b + carry) / 10;
        }
        return (carry > 0) ? '1' + res : res;
    }
};

// 5. Longest Palindromic Substring
class Solution {
// Time O(n^2), Space O(1) 
public:
    string longestPalindrome(string s) {
        const int n = s.size();
        // &: Lambdas modify local variables through **capture-by-reference*
        auto getLen = [&] (int left, int right) {
            while (left >= 0 && right < n && s[left] == s[right]) {
                --left; ++right;
            }
            return right - left + 1 - 2io9; // -2: left and right point to non palindromic char
        };
        int start = 0, maxLen = 0;
        for (int i = 0; i < n; ++i) {
            // center of the palindromic: odd, or even positions
            int curLen = max(getLen(i, i), getLen(i, i + 1));
            if (curLen > maxLen) {
                maxLen = curLen;
                start = i - (maxLen - 1) / 2; // update
            }
        }
        return s.substr(start, maxLen);
    }
};

// 6. Zigzag Conversion
// Input: s = "PAYPALISHIRING", numRows = 3; Output: "PAHNAPLSIIGYIR"
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) return s;
        vector<string> vec(numRows);
        int i = 0, n = s.size();
        
        while (i < n) {
            for (int row = 0; row < numRows && i < n; row++) {
                vec[row] += s[i++];
            }
            for (int row = numRows - 2; row >= 1 && i < n; row--) {
                vec[row] += s[i++];
            }
        }
        
        string res = "";
        for (string s : vec) res += s;
        
        return res;
    }
};

// 13. Roman to Integer
// Input: s = "MCMXCIV"; Output: 1994
// Explanation: M = 1000, CM = 900, XC = 90 and IV = 4.
class Solution {
public:
    int romanToInt(string s) {
        unordered_map<char, int> dict = {{'I', 1}, {'V', 5}, {'X', 10}, 
                                         {'L', 50}, {'C', 100}, {'D', 500}, {'M', 1000}};
        int res = 0, n = s.size();
        for (int i = 0; i < n; i++) {
            if (i == n - 1 || dict[s[i]] >= dict[s[i + 1]]) res += dict[s[i]];
            else res -= dict[s[i]];
        }
        
        return res;
    }
};
// 12. Integer to Roman
class Solution {
public:
    string intToRoman(int num) {
        vector<int> val = {1000, 900, 500, 400, 100,
                          90, 50, 40, 10, 
                           9, 5, 4, 1};
        vector<string> str = {"M", "CM", "D", "CD", "C",
                             "XC", "L", "XL", "X", 
                              "IX", "V", "IV", "I"};
        string res = "";
        for (int i = 0; i < val.size(); i++) {
            while (num >= val[i]) {
                res += str[i];
                num -= val[i];
            }
        }
        return res;
    }
};

// 28. Implement strStr()
// Input: haystack = "hello", needle = "ll"; Output: 2
class Solution {
public:
    int strStr(string haystack, string needle) {
        if (needle.empty()) return 0;
        
        int m = haystack.size(), n = needle.size();
        if (m < n) return -1;
        
        for (int i = 0; i <= m - n; i++) {  // NOTE, <=
            int j = 0;
            for (; j < n; j++) {
                if (haystack[i + j] != needle[j]) break;
            }
            if (j == n) return i;
        }
        
        return -1;
    }
};
























