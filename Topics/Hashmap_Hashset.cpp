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