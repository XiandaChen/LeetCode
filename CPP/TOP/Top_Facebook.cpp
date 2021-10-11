// 973. K Closest Points to Origin
// Min-queue
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<vector<int>> res;
        auto cmp = [](vector<int> & a, vector<int> & b) {
            return a[0] * a[0] + a[1] * a[1] > b[0] * b[0] + b[1] * b[1]; // min-queue
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        for (auto point : points)
            q.push(point);
        for (int i = 0; i < K; ++i) {
            res.push_back(q.top());
            q.pop();
        }
        return res;
    }
};

// 658. Find K Closest Elements
// Given a sorted array, two integers k and x, find the k closest elements to x in the array.
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res = arr;
        while (k < res.size()) {
            if (abs(x - res.front()) <= abs(res.back() - x))
                // res.erase(res.end()); // error
                res.pop_back();
            else
                res.erase(res.begin());
        }
        return res;
    }
};

// 438. Find All Anagrams in a String
// Find all the start indices of p's anagrams in s
class Solution {
public:
    vector<int> findAnagrams(string s, string p) {
        if (s.empty()) return {};
        unordered_map<char, int> ms, mp; // char-num
        vector<int> res;
        // first chars of size of p.size()
        for (int i = 0; i < p.size(); ++i) {
            ++ms[s[i]]; ++mp[p[i]];
        }
        // if ms==mp
        if (ms == mp) res.push_back(0);
        // rest chars after p.size()
        for (int i = p.size(); i < s.size(); ++i) {
            // move the window forward by one char
            if (--ms[s[i - p.size()]] == 0) ms.erase(s[i - p.size()]);
            ++ms[s[i]];
            if (ms == mp) res.push_back(i - p.size() + 1);
        }
        return res;
    }
};

// 560. Num of (Continue) Subarray Sum Equals K
//  accumulative sum
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        if (nums.empty()) return 0;
        vector<int> sums (nums.size());
        sums[0] = nums[0];
        int res = 0;
        // accumulative subarray sums
        for (int i = 1; i < nums.size(); ++i) 
            sums[i] = sums[i - 1] + nums[i];
        // find continue subarray sum equals k
        for (int i = 0; i < nums.size(); ++i) {
            if (sums[i] == k) ++res; // not forget
            for (int j = i - 1; j >= 0; --j) {
                if (sums[i] - sums[j] == k) ++res;
            }
        }
        return res;
    }
};
// O(N)
class Solution {
public:
    int subarraySum(vector<int>& nums, int k) {
        if (nums.empty()) return 0;
        unordered_map<int, int> cnt{{0, 1}}; // sum-cnt
        int res = 0, curSum = 0;
        for (int num : nums) {
            curSum += num;
            res += cnt[curSum - k];
            ++cnt[curSum];
        }
        return res;
    }
};

// 523. Continuous Subarray (at least size 2) Sum equal to a multiple of K
// Input: [23, 2, 4, 6, 7],  k=6; Output: True
// accumulative sum, O(n^2)
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
// O(N)
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.empty()) return false;
        unordered_map<int, int> m; // sum%k -- first index
        m[0] = -1;
        int sum = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            if (k != 0) sum %= k; // remainder
            if (m.count(sum)) {
                if (i - m[sum] > 1) return true; // at leat size 2
            }
            else m[sum] = i;  // must, only recorde the first occurrance
        }
        return false;
    }
};

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.empty()) return false;
        unordered_map<int, int> m; // sum%k -- first index
        m[0] = -1;
        int sum = 0, n = nums.size();
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            if (k != 0) sum %= k; // remainder
            if (m.count(sum)) {
                if (i - m[sum] > 1) return true; // at leat size 2
            }
            else m[sum] = i;  // must, only recorde the first occurrance
        }
        return false;
    }
};
// hash map, O(n)
class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        int n = nums.size(), sum = 0;
        // if (a%c == b%c), then (a-b)%c == 0
        unordered_map<int, int> m{{0, -1}}; // sum%k--indx
        for (int i = 0; i < n; ++i) {
            sum += nums[i];
            int remainder = (k == 0) ? sum : (sum % k);
            if (m.count(remainder)) {
                // length of at least 2
                // subarray [m[remain]+1, i] sum is a multiple of k
                if (i - m[remainder] > 1) return true; 
            }
            else {
                m[remainder] = i;
            }
        }
        return false;
    }
};

// 1249. Minimum Remove to Make Valid Parentheses
// Input: s = "(a(b(c)d)";  Output: "a(b(c)d)"
class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int open = 0, close = count(s.begin(), s.end(), ')'); // count all ')'
        string res = "";
        for (char c : s) {
            if (c == '(') {
                if (open == close) continue; // no more ')'
                ++open;
            }
            else if (c == ')') {
                --close; // decrease close num
                if (open == 0) continue; // no existing '('
                --open; // decrease open num after pairing '()'
            }
            res += c;
        }
        return res;
    }
};

// 71. Simplify Path
// Input: "/a/./b/../../c/"; Output: "/c"
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

// 133. Clone Graph, BFS
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

// 211. Add and Search Word - Data structure design
class WordDictionary {
public:
    struct TrieNode {
        TrieNode * child[26]; // assume letters a-z
        bool isWord;
        TrieNode(): isWord(false) {
            for (auto & a : child) a = nullptr; // & a
        }
    };
    /** Initialize your data structure here. */
    WordDictionary() {
        root = new TrieNode();
    }    
    /** Adds a word into the data structure. */
    void addWord(string word) {
        TrieNode * p = root;
        for (auto a : word) {
            int i = a - 'a';
            if (!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->isWord = true;
    }
    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */
    bool search(string word) {
        return search_DFS(word, root, 0);
    }
    bool search_DFS(string & word, TrieNode * p, int indx) {
        if (indx == word.size()) return p->isWord;
        if (word[indx] == '.') { // check all cases for next char
            for (auto a : p->child) {
                if (a && search_DFS(word, a, indx + 1)) return true;
            }
            return false;
        }
        
        return p->child[word[indx] - 'a'] && search_DFS(word, p->child[word[indx] - 'a'], indx + 1);
    }
private:
    TrieNode * root;
};

// 34. Find First and Last Position of Element in Sorted Array
// Binary search, O(logn)
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res (2, -1);
        int left = 0, right = nums.size();
        // find the leftmost index
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) left = mid + 1;
            else right = mid;
        }
        // check if leftindx is within the array bounds and target is in the array
        if (right == nums.size() || nums[right] != target) return res;
        res[0] = right;
        left = 0, right = nums.size();
        // find the rightmost index
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) left = mid + 1;
            else right = mid;
        }
        res[1] = right - 1;
        return res;
    }
};

// 56. Merge Intervals, merge all overlapping intervals.
// Input: [[1,3],[2,6],[8,10],[15,18]]; Output: [[1,6],[8,10],[15,18]]
class Solution {
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        if (intervals.empty()) return{};
        sort(intervals.begin(), intervals.end());
        vector<vector<int>> res{intervals[0]};
        for (int i = 1; i < intervals.size(); i++) {
            if (res.back()[1] >= intervals[i][0])
                //res.back()[1] = intervals[i][1];
                res.back()[1] = max(res.back()[1], intervals[i][1]);
            else
                res.push_back(intervals[i]);
        }
        return res;
    }
};
// 986. Interval List Intersections
// Input: A = [[0,2],[5,10],[13,23],[24,25]], B = [[1,5],[8,12],[15,24],[25,26]]
// Output: [[1,2],[5,5],[8,10],[15,23],[24,24],[25,25]]
class Solution {
public:
    vector<vector<int>> intervalIntersection(vector<vector<int>>& A, vector<vector<int>>& B) {
        vector<vector<int>> res;
        int m = A.size(), n = B.size(), ai = 0, bi = 0;
        while (ai < m && bi < n) {
            int aj = A[ai].size() - 1, bj = B[bi].size() - 1;
            if (A[ai][aj] < B[bi][0]) {
                ++ai;
            }
            else if (B[bi][bj] < A[ai][0]) {
                ++bi;
            }
            else {
                int c1 = max(A[ai][0], B[bi][0]), c2 = min(A[ai][aj], B[bi][bj]);
                res.push_back({{c1, c2}});
                if (A[ai][aj] < B[bi][bj]) ++ai;
                else ++bi;
            }
        }
        return res;
    }
};

// 139. Word Break
// Input: s = "applepenapple", wordDict = ["apple", "pen"]; Output: true
// DP
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(s.size() + 1); // dp[i]: s[0:i] is breakable
        dp[0] = true;
        for (int i = 0; i < dp.size(); ++i) { // dp.size(), not s.size()
            for (int j = 0; j < i; ++j) {
                if (dp[j] && wordSet.count(s.substr(j, i - j))) {
                    dp[i] = true;
                    break;
                }
            }
        }
        return dp.back();
    }
};
// Memoization
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set wordSet(wordDict.begin(), wordDict.end());
        vector<int> memo(s.size(), -1); // initial memo[]
        return wordBreak(s, wordSet, 0, memo);
    }
    bool wordBreak(string s, unordered_set<string> & wordSet, int start, vector<int> & memo) {
        if (start >= s.size()) return true;
        if (memo[start] != -1) return memo[start];
        for (int i = start + 1; i <= s.size(); ++i) {
            if (wordSet.count(s.substr(start, i - start)) && wordBreak(s, wordSet, i, memo))
                return memo[start] = 1;
        }
        return memo[start] = 0;
    }
};

// 253. Meeting Rooms II
// Find the minimum number of conference rooms required
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        auto cmp = [] (vector<int> & a, vector<int> & b) {
            return a[0] < b[0]; };
        sort(intervals.begin(), intervals.end(), cmp);
        priority_queue<int, vector<int>, greater<int>> q;
        for (auto intvl : intervals) {
            // being-used room gets free for new meeting
            if (!q.empty() && q.top() <= intvl[0]) q.pop();
            q.push(intvl[1]);
        }
        return q.size();
    }
};
// Facebook, Find maximum meetings fitted in one room.
int maxMeetingRooms(vector<vector<int>> & meetings) {
    if (meetings.size() == 0) return -1;   
    auto cmp = [] (vector<int> & a, vector<int> & b) {
        return a[1] < b[1]; // sort increasing by end time  
    };
    // Sorting of meeting according to their finish time. 
    sort(meetings.begin(), meetings.end(), cmp);    
    // vector for storing selected meetings
    // vector<int> m = {0};
	int res = 1;
    int endtime = meetings[0][1];    
    for (int i = 1; i < meetings.size(); ++i) {
        if (meetings[i][0] >= endtime) {
            // m.push_back(i);
			++res;
            endtime = meetings[i][1];
        }
    }   
    // return m.size();
	return res;
}

// 767. Reorganize String
// Rearrang so that two characters that are adjacent to each other (k=1) are not the same
class Solution {
public:
    string reorganizeString(string S) {
        map<char, int> m; // char-occurNum
        priority_queue<pair<int, char>> q; // max-heap, key=occurNum
        string res = "";
        for (char c : S) ++m[c];
        // construct max-heap
        for (auto a : m) {
            // some char occur more than half of the length
            if (a.second > (S.size() + 1) / 2) return ""; 
            q.push({a.second, a.first}); // or, q.push(make_pair(a.second, a.first)); 
        }
        while (q.size() >= 2) { // take two chars each time
            auto t1 = q.top(); q.pop();
            auto t2 = q.top(); q.pop();
            res += t1.second; // or, res.push_back(t1.second)
            res += t2.second;
            if (--t1.first) q.push(t1);
            if (--t2.first) q.push(t2);
        }
        // if one item left in the queue
        if (q.size() > 0) res += q.top().second;
        return res;
    }
};
// General K
class Solution {
public:
    string reorganizeString(string s) {
        int len = s.size(), k = 2;
        map<char, int> m;
        priority_queue<pair<int, char>> q;
        string res = "";
        for (char c : s) ++m[c];
        for (auto a : m)  q.push({a.second, a.first});
        while (!q.empty()) {
            vector<pair<int, char>> tmp; // to hold availabel items after processing
            int cnt = min(k, len); // take k item each time if len>=k
            for (int i = 0; i < cnt; ++i) {
                if (q.empty()) return ""; // check
                auto t = q.top(); q.pop();
                res += t.second;
                if (--t.first) tmp.push_back(t);
                --len;
            }
            for (auto a : tmp) q.push(a);
        }
        return res;
    }
};

// 621. Task Scheduler
// Input: tasks = ["A","A","A","B","B","B"], n = 2; Output: 8
// Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int res = 0, cycle = n + 1;
        unordered_map<char, int> m;
        priority_queue<int> q;
        for (char c : tasks) ++m[c];
        for (auto a : m) q.push(a.second);
        while (!q.empty()) {
            int cnt = 0;
            vector<int> t;
            for (int i = 0; i < cycle; ++i) {
                if (!q.empty()) {
                    t.push_back(q.top()); q.pop();
                    ++cnt;
                }
            }
            for (int d : t) {
                if (--d > 0) q.push(d);
            }
            res += q.empty() ? cnt : cycle;
        }
        return res;
    }
};

// 636. Exclusive Time of Functions, stack
// Return the exclusive time of each function, sorted by their function id.
// Input: n = 2; logs = ["0:start:0","1:start:2","1:end:5","0:end:6"]; Output: [3, 4]
class Solution {
public:
    vector<int> exclusiveTime(int n, vector<string>& logs) {
        vector<int> res(n, 0);
        stack<int> st; // func_id
        int pretime = 0;
        for (auto log : logs) {
            int pos1 = log.find(':'), pos2 = log.find_last_of(':');
            int id = stoi(log.substr(0, pos1));
            string type = log.substr(pos1 + 1, pos2 - pos1 - 1);
            int curtime = stoi(log.substr(pos2 + 1));
            
            if (type == "start") {
                if (!st.empty()) {
                    // suspend cur func
                    res[st.top()] += curtime - pretime; // start: very start of the time slot
                }
                st.push(id);
                pretime = curtime;
            }
            else { // "end"
                res[st.top()] += curtime - pretime + 1; // +1: end time: very end of the time slot
                st.pop();
                pretime = curtime + 1; // next log starts for next time slot
            }
        }
        return res;
    }
};

// 1004. Max Consecutive Ones III, Sliding window
// change up to K values from 0 to 1, to get the longest (contiguous) subarray of 1s. 
// Input: A = [1,1,1,0,0,0,1,1,1,1,0], K = 2; Output: 6; Explanation: [1,1,1,0,0,1,1,1,1,1,1]
class Solution {
public:
    int longestOnes(vector<int>& A, int K) {
        int left = 0, zeros = 0, res = 0;
        // sliding window: [left, right]
        for (int right = 0; right < A.size(); ++right) {
            if (A[right] == 0) ++zeros;
            // shift the window to right if zeros > K
            while (zeros > K) {
                if (A[left++] == 0) --zeros;
            }
            // update res
            res = max(res, right - left + 1);
        }
        return res;
    }
};

// 238. Product of Array Except Self
// see Facebook Explore

// 1249. Minimum Remove to Make Valid Parentheses
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

// 973. K Closest Points to Origin
// sorting, O(nlogn)
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        sort(points.begin(), points.end(), [](vector<int> & a, vector<int> & b) {
           return (a[0] * a[0] + a[1] * a[1] < b[0] * b[0] + b[1] * b[1]); 
        });
        return vector<vector<int>> (points.begin(), points.begin() + K);
    }
};
// hash map, O(n)
class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<vector<int>> res;
        auto cmp = [](vector<int> & a, vector<int> & b) {
            return a[0] * a[0] + a[1] * a[1] > b[0] * b[0] + b[1] * b[1]; // min-queue
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        for (auto point : points)
            q.push(point);
        for (int i = 0; i < K; ++i) {
            res.push_back(q.top());
            q.pop();
        }
        return res;
    }
};

// Find the leftmost column index with a 1 in it.
// In a binary matrix (all elements are 0 and 1), every row is sorted in ascending order (0 to the left of 1). 
// ref: Q1004 Max Consecutive Ones III, Sliding Window
int findLeftMostColumnOfOne(vector<vector<int>> & matrix) {
    // handle edge cases
    if (matrix.empty() || matrix[0].empty()) return -1;
    int rows = matrix.size(), cols = matrix[0].size();
    int res = -1;
    // Search from top right: go down if current element is 0, go left otherwise
    // Keep doing until we reach last row
    for (int r = 0, c = cols - 1; r < rows && c >= 0; ) {
        if (matrix[r][c] == 1) {
            res = c;
            --c;
        }
        else {
            ++r;
        }
    }
    return res;
}

//Find the maximum length of vacation an employee can take.
// ref. Q1004, sliding window 
int maxVacation(vector<bool> & days, int ptos) {
	int left = 0, numFalse = 0, res = 0;
	// count num of F within sliding window [left, right]
	for (int right = 0; right < days.size(); ++right) {
		if (!days[right]) ++numFalse;
		// shift the window to right if numFalse > ptos
		while (numFalse > ptos){
			if (!days[left++]) --numFalse; 
		}
		// update the length of maximum holiday
		res = max(res, right - left + 1);
	}
	return res;
}

// Find maximum meetings in one room.
int maxMeetingRooms(vector<vector<int>> & meetings) {
    if (meetings.size() == 0) return -1;    
    auto cmp = [] (vector<int> & a, vector<int> & b) {
        return a[1] < b[1]; // sort increasing by end time  
    };
    // Sorting of meeting according to their finish time. 
    sort(meetings.begin(), meetings.end(), cmp);   
    // vector for storing selected meetings
    // vector<int> m = {0};
	int res = 1;
    int endtime = meetings[0][1];    
    for (int i = 1; i < meetings.size(); ++i) {
        if (meetings[i][0] >= endtime) {
            // m.push_back(i);
			++res;
            endtime = meetings[i][1];
        }
    }   
    // return m.size();
	return res;
}

// Facebook, unique number in unsorted array, O(n)
// Input:  ar[] = {7, 3, 5, 4, 5, 3, 4}; Output: 7 
int uniqueNum (vector<int> & nums) {
	if (nums.size() == 0) return -1;
	// Do XOR of all elements
	// return the single occurrence
	int res = nums[0];
	for (int i = 1; i < nums.size(); ++i)
		res ^= nums[i];
	return res;
}
// Unique number in sorted array, O(logn)
// elements before unique num: first occurrence at even index (0,2,..), next at (1,3..)
// Input: arr[] = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8}; Output:  4
int uniqueNum (vector<int> & nums) {
	if (nums.size() == 0) return -1;	
    int n = nums.size(), left = 0, right = n - 1;
    while (left < right) {
        int mid = left + (right - left) / 2;       
        // If mid is even and element next to mid is 
        // same as mid, then output element lies on 
        // right side, else on left side 
        if (mid % 2 == 0) { // even pos
            if (mid + 1 < n && nums[mid] ==  nums[mid + 1]) left = mid + 2;
            else right = mid - 2;
        }
        else {
            if (mid - 1 >= 0 && nums[mid] == nums[mid - 1]) left = mid + 1;
            else right = mid - 1;
        }
    }
    return nums[right];
}

// Cut woods with max lenght
// ref. Q875. Koko Eating Bananas, Binary Search
int cutWoodMaxLen(vector<int> & woods, int k) {
    int left = 1, right = *max_element(woods.begin(), woods.end()); // #include <algorithm>
    while (left < right) {
        int mid = left + (right - left) / 2, cnt = 0;
        for (int wood : woods) {
            cnt += wood / mid; // num of pieces when cutting wood in lenght of mid
        }
		// increasing piece length
        if (cnt > k) left = mid + 1;  // error: if (cnt >= k)
        else right = mid;
    } 
    return right;
}

// 29. Divide Two Integers
class Solution {
public:
    int divide(int dividend, int divisor) {
        // corner case, (-2147483648) / (-1) > INT_MAX
        if (divisor == 0 || (dividend == INT_MIN && divisor == -1)) return INT_MAX;
        
        long m = labs(dividend), n = labs(divisor), res = 0;
        int sign = ((dividend < 0) ^ (divisor < 0)) ? -1 : 1;
        
        while (n <= m) { // m is one times more than n
            long tmp = n, p = 1;
            while ((tmp << 1) <= m) { // m is two times more than n, bit manipulation
                tmp <<= 1;
                p <<= 1;
            }
            m -= tmp;
            res += p;
        }
        
        return (sign == -1) ? -res : res;
    }
};