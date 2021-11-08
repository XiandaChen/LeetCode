// DAY 1
// 136. Single Number
// Input: [4,1,2,1,2];   Output: 4
// BitManuplation: Time O(N), Space O(1); unordered_map: Space O(N)
class Solution { // bit manuplation
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int num : nums) res ^= num;
        return res;
    }
};
class Solution { // unordered_map
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (int num : nums) mp[num] += 1;
        for (auto x : mp)
            if (x.second == 1) return x.first;
        return -1;
    }
};
// 137. Single Number II
// Input: [0,1,0,1,0,1,99];   Output: 99
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0; // 32-bit num
        // add up value of each bit pos of nums, then mod to 3
        for (int i = 0; i < 32; ++i) {
            int sum = 0;
            for (int num : nums)
                sum += (num >> i) & 1; // i-th bit value
            res |= (sum % 3) << i; // num of ith-bit=1 appears three times
        }
        return res;
    }
};
// 260. Single Number III
// Input:  [1,2,1,3,2,5];  Output: [3,5]
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        // [1,2,1,3,2,5] => diff=3^5='110', i.e., difference at 2nd and 3rd bit
        // int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        int diff = 0;
        for (int num : nums) diff ^= num;
        // split '110' into '100' and '010'
        int mask = diff & -diff;  // numder of rightmost set bit, '10'
        vector<int> res(2, 0);
        for (int num : nums) {
            if (num & mask) res[0] ^= num;
            else res[1] ^= num;
        }
        return res;
    }
};


/// DAY 2
// 202. Happy Number
// Input: 19; Output: true
// Explanation: 
// 12 + 92 = 82
// 82 + 22 = 68
// 62 + 82 = 100
// 12 + 02 + 02 = 1
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> st;
        while (n != 1) {
            string num = to_string(n);
            int sum = 0;
            for (int i = 0; i < size(num); ++i)
                sum += pow(num[i] - '0', 2);
            if (st.count(sum)) break;
            else st.insert(sum);
            n = sum;
        }
        return n == 1;
    }
};
// 263. Ugly Number
// positive numbers whose prime factors only include 2, 3, 5.
class Solution {
public:
    bool isUgly(int num) {
        while (num >= 2) {
            if (num % 2 == 0) num /= 2;
            else if (num % 3 == 0) num /=3;
            else if (num % 5 == 0) num /= 5;
            else break;
        }
        return num == 1;
    }
};
// 258. Add Digits (Digital root of a num)
// Input: 38;   Output: 2 
// Explanation: The process is like: 3 + 8 = 11, 1 + 1 = 2.
class Solution {
public:
    int addDigits(int num) {
        while (num >= 10) { // must be >=
            int sum = 0;
            while (num) {
                sum += (num % 10);
                num /= 10;
            }
            num = sum;
        }
        return num;
    }
};
// 141. Linked List Cycle
// Given a linked list, determine if it has a cycle in it.
class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode * slow = head, * fast = head;
        while (fast && fast->next) {
            slow = slow->next;      // one step
            fast = fast->next->next; // two steps, must check fast->next exist 
            if (slow == fast) return true;
        }
        return false;
    }
};
// 142. Linked List Cycle II
// Given a linked list, return the node where the cycle begins. 
// If there is no cycle, return null.
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode * slow = head, * fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) break;  // cycle exists
        }
        if (!fast || !fast->next) return NULL; // must check, no cycle
        slow = head;
        while (slow != fast) {
            slow = slow->next;
            fast = fast->next;
        }
        return slow;
    }
};

// DAY 3
// 53. Maximum (continuous) Subarray
// Input: [-2,1,-3,4,-1,2,1,-5,4],
// Output: 6;  Explanation: [4,-1,2,1] has the largest sum = 6.
class Solution {	// Greedy: O(n)
public:
    int maxSubArray(vector<int>& nums) {
        int res = INT_MIN, curSum = 0;
        for (int num : nums) {
            curSum = max(curSum + num, num);
            res = max(res, curSum);
        }
        return res;
    }
};
class Solution {	// DC : O(logn)
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.empty()) return 0;
        return helper(nums, 0, nums.size() - 1);
    }
    int helper(vector<int> & nums, int left, int right) {
        if (left >= right) return nums[left]; // must be >=, not ==
        int mid = left + (right - left) / 2;
        int lmax = helper(nums, left, mid - 1);
        int rmax = helper(nums, mid + 1, right);
        // start from nums[mid] to calculate mid-maxSubArray
        int mmax = nums[mid], tmp = mmax;
        // extent midmax-subarray from mid to left
        for (int i = mid - 1; i >= left; --i) { // must be >=, not >
            tmp += nums[i];
            mmax = max(mmax, tmp);
        }
        // extent midmax-subarray from mid to right
        tmp = mmax;
        for (int i = mid + 1; i <= right; ++i) { // must be <=, not <
            tmp += nums[i];
            mmax = max(mmax, tmp);
        }
        return max(mmax, max(lmax, rmax));
    }
};

// DAY 4
// 283. Move Zeroes  (swap vector)
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
// 27. Remove Element  (swap iterator)
// nums = [0,1,2,2,3,0,4,2], val = 2,
// return length = 5, nums=[0,1,3,0,4].
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        auto it = nums.begin(), jt = it;
        for (; it != nums.end(); ++it) {
            if (*it != val)
                iter_swap(it, jt++);
        }
        nums.erase(jt, nums.end());
        return nums.size();
    }
};

// DAY 5
//  121. Best Time to Buy and Sell Stock
// at most one transaction
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0, buy = INT_MAX;
        for (int price : prices) {
            buy = min(buy, price);  // min buy-price untill now
            res = max(res, price - buy); // update maxprofit
        }
        return res;
    }
};
// 122. Best Time to Buy and Sell Stock II
// as many transactions as you like
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
		// must be (int) in for loop in case of input []
		// or, define int res = 0, n = prices.size();
        // 		      for (int i = 0; i < - 1; ++i) 
        for (int i = 0; i < (int)prices.size() - 1; ++i) { 
            if (prices[i] < prices[i + 1])
                res += prices[i + 1] - prices[i];
        }
        return res;
    }
};
// 123. Best Time to Buy and Sell Stock III (DP)
// at most two transactions.
// local[i,j]: maxprofit when complete at most j transactions till day i, 
//			and the last transaction is completed on day id
// global[i,j]: maxprofit when complete at most j transactions till day i
// local[i][j] = max(global[i - 1][j - 1], local[i - 1][j]) + diff
// {original: local[i][j] = max(global[i - 1][j - 1] + max(diff, 0), local[i - 1][j] + diff)}
// global[i][j] = max(local[i][j], global[i - 1][j])
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size(), k = 3; // k = 3 for two transactions
        vector<vector<int>> global(n, vector<int>(k, 0)), local(n, vector<int>(k, 0));
        for (int i = 1; i < n; ++i) {
            int diff = prices[i] - prices[i - 1];
            for (int j = 1; j < k; ++j) {
                local[i][j] = max(global[i - 1][j - 1], local[i - 1][j]) + diff;
                global[i][j] = max(local[i][j], global[i - 1][j]);
            }
        }
        return global.back().back();
    }
};
// 309. Best Time to Buy and Sell Stock with 1-day Cooldown
// Actions: you have 1 stock and you sell it
// 			you have 1 stock and you do nothing
// 			you have 0 stock and you buy stock i
// 			you have 0 stock and you do nothing
// Transictions: action at day-i depends on day-(i-1)
// 		if you take action 1 on day i 
// 		==> you have either taken action 2 or 3 on day i-1
// 		if you take action 2 on day i 
// 		==> you have either taken action 2 or 3 on day i-1
// 		if you take action 3 on day i 
// 		==> you must have taken action 4 on day i-1 (you can not sell on day i-1 due to cool down)
// 		if you take action 4 on day i 
//		==> you have either taken action 1 or 4 on day i-1
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int L = prices.size();
        if(L < 2) return 0;
        
        // profit at day-i
        int has1_Sell = 0;  // action: have stock and sell it
        int has1_doNothing = -prices[0];  // have stock and do nothing
        int has0_Buy = -prices[0];      // have no stock and buy it
        int has0_doNothing = 0;         // have no stock and do nothing
        for(int i = 1; i < L; ++i) {
            has1_doNothing = has1_doNothing > has0_Buy ? has1_doNothing : has0_Buy;
            has0_Buy = -prices[i] + has0_doNothing;
            has0_doNothing = has0_doNothing > has1_Sell ? has0_doNothing : has1_Sell;
            has1_Sell = prices[i] + has1_doNothing;
        }
        return has1_Sell > has0_doNothing ? has1_Sell : has0_doNothing;
    }
};

// DAY 6
// 49. Group Anagrams
// Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
// Output: [["ate","eat","tea"], ["nat","tan"], ["bat"]]
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> m; // string--anagrams
        vector<vector<string>> res;
        for (string str : strs) { // group anagrams
            string t = str; // we don't want to modify input strs
            sort(t.begin(), t.end());
            m[t].push_back(str);
        }
        for (auto a : m) { // recorde outputs
            res.push_back(a.second);  // map: m.first, m.second
        }
        return res;
    }
};
// 242. Valid Anagram
class Solution {
public:
    bool isAnagram(string s, string t) {
        vector<int> s_cnt(26), t_cnt(26);
        for (char c : s) ++s_cnt[c - 'a'];
        for (char c : t) ++t_cnt[c - 'a'];
        return s_cnt == t_cnt;
    }
};
// 438. Find All Anagrams in a String
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        vector<int> res;
        unordered_map<char, int> ms, mp; // char-num
        for (int i = 0; i < p.size(); ++i) {
            ++ms[s[i]]; ++mp[p[i]];
        }
        if (ms == mp) res.push_back(0);
        for (int i = p.size(); i < s.size(); ++i) {
            // --ms[s[i - p.size()]]; // error
            if (--ms[s[i - p.size()]] == 0) ms.erase(s[i - p.size()]);
            ++ms[s[i]];
            if (ms == mp) res.push_back(i - p.size() + 1);
        }
        return res;
    }
};

// DAY 7
// Given an integer array arr, count element x such that x + 1 is also in arr.
// 1,1,1,2,2,4,5,5,6 => 4
class Solution { // time: O(n), space: O(n)
public:
    int countElements(vector<int>& arr) { 
        unordered_set<int> st;
        int res = 0;
        for (int a : arr) st.insert(a);
        for (int a : arr) 
            if (st.count(a + 1)) ++res;
        return res;
    }
};
class Solution { // time: O(nlogn), space: O(1)
public:
    int countElements(vector<int>& arr) { 
        // 1,1,1,2,2,4,5,5,6 => 4
        if (arr.size() < 2) return 0;
        int res = 0;
        sort(arr.begin(), arr.end());
        int i = 0, j = 1;
        while (j < arr.size()) {
            if (arr[i] == arr[j]) ++j; // same, move j forward
            else if (arr[i] + 1 == arr[j]) { // count
                res += 1;
                ++i;
            }
            else { // arr[i]!=arr[j], move i forward
                ++i;
            }
        }
        return res;
    }
};

// DAY 8
// Middle of the Linked List
class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        ListNode * slow = head, * fast = head;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }
};

// DAY 9
// 844. Backspace String Compare
// Input: S = "a##c", T = "#a#c"; Output: true
class Solution {  // time:  O(n); space: O(n)
public:
    bool backspaceCompare(string S, string T) {
        string ss, st;  // stack<char> ss, st;
        for (char c : S) {
            // error, if S:"y#f#o##f" => ss:"#f"; T: "y#fo##f" => st:"f"
            // if (!ss.empty() && c == '#') ss.pop_back();
            // else ss.push_back(c);
            if (c != '#') ss.push_back(c); //stack: ss.push(c);
            else {
                if (!ss.empty()) ss.pop_back(); //stack: ss.pop();
            }
        }
        for (char c : T) {
            if (c != '#') st.push_back(c); //stack: st.push(c);
            else {
                if (!st.empty()) st.pop_back(); //stack: st.pop();
            }
        }
        return ss == st;  
    }
};
class Solution { // time: O(n), Space: O(1)
public:
    bool backspaceCompare(string S, string T) {
        int i = S.size() - 1, j = T.size() - 1;
        int cnt_i = 0, cnt_j = 0;
        // while (i >= 0 && j >= 0) { // error, S: "nzp#o#g", T: "b#nzp#o#g"
        while (i >= 0 || j >= 0) {
            while (i >= 0 && (S[i] == '#' || cnt_i > 0)) { // backspace
                S[i--] == '#' ? ++cnt_i : --cnt_i;
            }
            while (j >= 0 && (T[j] == '#' || cnt_j > 0)) {
                T[j--] == '#' ? ++cnt_j : --cnt_j;
            }
            if (i < 0 || j < 0) return i == j; // out of loop
            if (S[i--] != T[j--]) return false;
        }
        return i == j;
    }
};

// DAY 10
// 543. Diameter of Binary Tree
class Solution {
public:
    int diameterOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        // path via root: sum of height of root->left and right
        int res = getHeight(root->left) + getHeight(root->right);
        // max path: via root, or not (on root->left or root->right)
        return max(res, max(diameterOfBinaryTree(root->left), 
                           diameterOfBinaryTree(root->right)));
    }
    // height (max node-leaf) of a node
    int getHeight(TreeNode * node) {
        if (!node)  return 0;
        if (m.count(node)) return m[node];
        int left = getHeight(node->left);
        int right = getHeight(node->right);
        return m[node] = max(left, right) + 1;
    }
private:
    unordered_map<TreeNode*, int> m; // <node, height>
};
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

// DAY 11



















