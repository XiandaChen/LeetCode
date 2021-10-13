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
    int subarraySum(vector<int>& nums, int k) { // Time Limit Exceeded
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

// 827. Making A Large Island
// allowed to change at most one 0 to be 1.
class Solution { // Time Limit Exceeded!
public:
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 0;
        bool hasZero = false;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) continue;
                
                hasZero =  true;
                
                grid[i][j] = 1; // change 0 to 1, then search num ones starting from [i][j]
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                res = max(res, helper(grid, i, j, visited));
                if (res == m * n) return res; // NOTE
                grid[i][j] = 0; // reset [i][j]
            }
        }
        
        return (hasZero) ? res : m * n;
    }
    
    int helper(vector<vector<int>>& grid, int i, int j, vector<vector<bool>> & visited) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0 || visited[i][j]) return 0;
        
        visited[i][j] = true;
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int res = 1;  // 1 for current [i][j]
        for (auto & dir : dirs) {
            res += helper(grid, i + dir[0], j + dir[1], visited);
        }
        return res;
    }
};

// 235. Lowest Common Ancestor of a Binary Search Tree
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root) return nullptr;
        
        if (root->val > p->val && root->val > q->val) 
            return lowestCommonAncestor(root->left, p, q);
        
        if (root->val < p->val && root->val < q->val)
            return lowestCommonAncestor(root->right, p, q);
        
        return root;
    }
};
// 236. Lowest Common Ancestor of a Binary Tree
// TreeNode *p and *q exist in the tree
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root; // one of p/q to be ancestor of the other
        
        TreeNode * left = lowestCommonAncestor(root->left, p, q);
        TreeNode * right = lowestCommonAncestor(root->right, p, q);
        
        // if p and q exist at two diff sides, root is the ancestor
        if (left && right) return root;
        
        return (left) ? left : right;
    }
};
// 1644. Lowest Common Ancestor of a Binary Tree II
// If either node p or q does not exist in the tree, return null. All values of the nodes in the tree are unique.
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (checkIfExists(root, p) && checkIfExists(root, q))
            return lca(root, p, q);
        else
            return NULL;
    }
    
    TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (!root || root == p || root == q) return root; // one of p/q to be ancestor of the other
        
        TreeNode * left = lca(root->left, p, q);
        TreeNode * right = lca(root->right, p, q);
        
        // if p and q exist at two diff sides, root is the ancestor
        if (left && right) return root;
        
        return (left) ? left : right;
    }
    
    bool checkIfExists(TreeNode* root, TreeNode* node){
        if(root == NULL || node == NULL)
            return false;
        if(root->val == node->val)
            return true;
        if(checkIfExists(root->left, node) || checkIfExists(root->right, node))
            return true;
        
        return false;
    }
};
// 1650. Lowest Common Ancestor of a Binary Tree III
// Given two nodes of a binary tree p and q, return their lowest common ancestor (LCA).
// Each node will have a reference to its parent node. 
class Solution {
public:
    Node* lowestCommonAncestor(Node* p, Node * q) {
        if (p == NULL || q == NULL || p == q) return p;
        
        if (search(p, q)) return p;
        else if (search(q, p)) return q;
        else return lowestCommonAncestor(p->parent, q->parent);
    }
    
    bool search(Node * root, Node * node) { // check if node in root
        if (!root) return false;
        
        if (root == node || search(root->left, node) || search(root->right, node))
            return true;
        else 
            return false;
    }
};
// 1676. Lowest Common Ancestor of a Binary Tree IV
// Given the root of a binary tree and an array of TreeNode objects nodes
class Solution {
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, vector<TreeNode*> &nodes) {
        if (!root) return NULL;
        
        if (nodes.size() == 1) return nodes[0];
        
        for (auto & node : nodes) {
            if (node == root) return root;  // if nodes include root
        }
        
        bool left = search(root->left, nodes);
        bool right = search(root->right, nodes);
        
        if (left && right) { // nodes exist in both left and right sides
            return root;
        }
        else if (left) {
            return lowestCommonAncestor(root->left, nodes);
        }
        else {
            return lowestCommonAncestor(root->right, nodes);
        }
    }
    
    // true: if there is a node in current tree
    bool search(TreeNode* root, vector<TreeNode*> &nodes) {
        if (!root) return false;
        for (auto & node : nodes) {
            if (root->val == node->val) return true;
        }
        return search(root->left, nodes) || search(root->right, nodes);
    }
};

// 1762. Buildings With an Ocean View
// a building has an ocean view if all the buildings to its right have a smaller height.
// Input: heights = [4,2,3,1]; Output: [0,2,3]
class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        int n = heights.size(), curMax = 0;
        vector<int> maxRight(n), res;
        
        maxRight[n - 1] = 0;
        
        for (int i = n - 2; i >= 0; i--){
            curMax = max(curMax, heights[i + 1]);
            maxRight[i] = curMax;
        }
        
        for (int i = 0; i < n; i++) {
            if (heights[i] > maxRight[i]) res.push_back(i);
        }
        
        return res;
    }
};

// 1047. Remove All Adjacent Duplicates (size of two) In String
// Input: s = "abbaca"; Output: "ca"
// Input: s = "aaaaaaaaa"; Output: "a"
class Solution {
public:
    string removeDuplicates(string s) {
        stack<char> st;
        string res;
        
        for (char c : s) {
            if (st.empty()) st.push(c);
            else if (st.top() == c) st.pop(); // remove adjacent duplicates
            else st.push(c);
        }
        
        while (!st.empty()) {
            res.push_back(st.top());
            st.pop();
        }
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};
// 1209. Remove All Adjacent Duplicates in String II
// Input: s = "deeedbbcccbdaa", k = 3; Output: "aa"
// Input: s = "pbbcggttciiippooaais", k = 2; Output: "ps"
class Solution {
public:
    string removeDuplicates(string s, int k) {
        stack<pair<char, int>> st; // char-cnt
        string res;
        
        for (char c : s) {
            if (st.size() > 0 && st.top().first == c) st.top().second++;
            else st.push({c, 1});
            
            if (st.top().second == k) st.pop();
        }
        
        while (!st.empty()) {
            while (st.top().second--) {
                res.push_back(st.top().first);
            }
            st.pop();
        }
        
        reverse(res.begin(), res.end());
        
        return res;
    }
};

// 1382. Balance a Binary Search Tree
class Solution {
public:
    TreeNode* balanceBST(TreeNode* root) {
        vector<TreeNode*> orders;
        inorder(root, orders);
        return buildBST(orders, 0, orders.size() - 1); // build BST using mid node as root
    }
    
    void inorder(TreeNode* root, vector<TreeNode*> & orders) {
        if (!root) return;
        inorder(root->left, orders);
        orders.push_back(root);
        inorder(root->right, orders);
    }
    
    TreeNode * buildBST(vector<TreeNode*> & orders, int start, int end) {
        if (start > end) return NULL; // NOTE, must
        int mid = start + (end - start) / 2;
        
        TreeNode * node = orders[mid];
        node->left = buildBST(orders, start, mid - 1);
        node->right = buildBST(orders, mid + 1, end);
        
        return node;
    }
};

// 766. Toeplitz Matrix
// A matrix is Toeplitz if every diagonal from top-left to bottom-right has the same elements.
class Solution {
public:
    bool isToeplitzMatrix(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (i > 0 && j > 0 && matrix[i - 1][j - 1] != matrix[i][j]) return false;
            }
        }
        return true;
    }
};

// 422. Valid Word Square
// Input: words = ["abcd","bnrt","crmy","dtye"]; Output: true
// Input: words = ["abcd","bnrt","crm","dt"]; Output: true
class Solution {
public:
    bool validWordSquare(vector<string>& words) {
        if (words.empty()) return false;

        // NOTE, words[i].size() may be equal to words[j].size() for i!=j
        for (int i = 0; i < words.size(); i++) {
            for (int j = 0; j < words[i].size(); j++) {
                // if not symmetric
                if (j >= words.size() || i >= words[j].size()) return false;
                
                if (i != j && words[i][j] != words[j][i]) return false;
            }
        }
        
        return true;
    }
};

// 408. Valid Word Abbreviation
class Solution {
public:
    bool validWordAbbreviation(string word, string abbr) {
        int i = 0, j = 0, m = word.size(), n = abbr.size();
        
        while (i < m && j < n) {
            if (isdigit(abbr[j])) {
                if (abbr[j] == '0') return false; // abbr not start with 0
                
                int cnt = 0;
                while (j < n && isdigit(abbr[j])) {
                    cnt = cnt * 10 + (abbr[j++] - '0');
                }
                
                i += cnt;                
            }
            else {
                if (word[i++] != abbr[j++]) return false;
            }
        }
        
        return i == m && j == n;
    }
};

// 42. Trapping Rain Water
class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0, left = 0, right = height.size() - 1;
        
        while (left < right) {
            int boundBar = min(height[left], height[right]);
            
            if (boundBar == height[left]) {
                left++;
                while (left < right && boundBar > height[left]) {
                    res += (boundBar - height[left++]);
                }
            }
            else {
                right--;
                while (left < right && boundBar > height[right]) {
                    res += (boundBar - height[right--]);
                }
            }
        }
        
        return res;
    }
};

// 31. Next Permutation
class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size(), i = n - 2, j = n - 1;
        // find the first drop from right, 2 in [1,2,7,4,3,1]
        while (i >= 0 && nums[i] >= nums[i + 1]) i--;
        // find the first larger than 2 from right, 3, in [1,2,7,4,3,1]
        if (i >= 0) { // NOTE, in case [3, 2, 1]
            while (j >= i && nums[j] <= nums[i]) j--;
            swap(nums[i], nums[j]); // [1,3,7,4,2,1]
            
        }
        reverse(nums.begin() + i + 1, nums.end());
    }
};

// 215. Kth Largest Element in an Array
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (true) {
            int pos = divide(nums, left, right);
            
            if (pos == k - 1) return nums[pos];
            else if (pos > k - 1) right = pos - 1;
            else left = pos + 1;
        }
    }
    int divide(vector<int> & nums, int start, int end) { // quick sort
        int pivot = nums[start], left = start + 1, right = end;
        while (left <= right) { // NOTE, <=
            if (nums[left] < pivot && nums[right] > pivot) {
                swap(nums[left++], nums[right--]);
            }
            else if (nums[left] >= pivot) {
                left++;
            }
            else if (nums[right] <= pivot) {
                right--;
            }
        }
        swap(nums[start], nums[right]);
        return right;
    }
};

// 680. Valid Palindrome II
class Solution {
public:
    bool validPalindrome(string s) {
        int left = 0, right = s.size() - 1;
        while (left < right) {
            if (s[left] != s[right]) {
                return isPalindrome(s, left, right - 1) || isPalindrome(s, left + 1, right);
            }
            left++;
            right--;
        }
        return true;
    }
    bool isPalindrome(string s, int left, int right) {
        while (left < right) { // NOTE, < : s = "abca" is true
            if (s[left] != s[right]) return false;
            left++;
            right--;
        }
        return true;
    }
};

// 528. Random Pick with Weight
class Solution {
public:
    Solution(vector<int>& w) {
        // sum[0] = w[0]; // error
        sum = w;
        for (int i = 1; i < w.size(); ++i)
            sum[i] = sum[i - 1] + w[i];
    }
    int pickIndex() {
        // w=[1,3,2], sum=[1,4,6], x=rand()%6=[0,~,5]
        // x=0 -> w1; x=[1,2,3] -> w2; x=[4,5] -> w3
        int x = rand() % sum.back();
        int left = 0, right = sum.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (sum[mid] <= x) left = mid + 1; // error '<', sum is 1-indexed, x is 0-indexed
            else right = mid;
        }
        return left;
    }
private:
    vector<int> sum; // accumulative sum
};

// 124. Binary Tree Maximum Path Sum
class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int res = INT_MIN;
        maxPathToLeaf(root, res);
        return res;
    }
    int maxPathToLeaf(TreeNode * node, int & res) { // maxsum of path from cur node to a leaf 
        if (!node) return 0;
        int left = max(maxPathToLeaf(node->left, res), 0); // maxPathSum of path rooting a node->left
        int right = max(maxPathToLeaf(node->right, res), 0);
        res = max(res, left + right + node->val);
        return max(left, right) + node->val; // only max(left, right)
    }
};

// 227. Basic Calculator II
class Solution {
public:
    int calculate(string s) {
        if (s.empty()) return 0; // corner case
        int n = s.size(), res = 0, lastNum = 0, curNum = 0;
        char lastOp = '+';  // previous operator: 1+2*3 => 0+1+2*3
        for (int i = 0; i < n; ++i) {
            char curChar = s[i];
            if ('0' <= curChar && curChar <= '9') curNum = curNum * 10 + (curChar - '0');
            
            if (i == n - 1 || curChar == '+' || 
                curChar == '-' || curChar == '*' || curChar == '/') {
                if (lastOp == '+' || lastOp == '-') {
                    res += lastNum;
                    lastNum = (lastOp == '+') ? curNum : -curNum;
                }
                else if (lastOp == '*') {
                    lastNum *= curNum;
                }
                else if (lastOp == '/') {
                    lastNum /= curNum;
                }
                lastOp = curChar;
                curNum = 0;
            }
        }
        return res + lastNum;  // must, add the very last num
    }
};

// 953. Verifying an Alien Dictionary
class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> umap; // char-order
        
        for (int i = 0; i < (int)order.size(); i++) {
            umap[order[i]] = i;
        }
        
        for (int i = 1; i < (int)words.size(); i++) {
            int j = 0, m = words[i - 1].size(), n = words[i].size();
            for (; j < min(m, n); j++) {
                if (umap[words[i - 1][j]] < umap[words[i][j]]) break; // sorted
                else if (umap[words[i - 1][j]] == umap[words[i][j]]) continue; // check next pair
                else return false;
            }
            if (m > n && j == n) return false;  // first word is longer than second word
        }
        
        return true;
    }
};
// 269. Alien Dictionary
class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_map<char, vector<char>> graph; // parent-children
        unordered_map<char, int> indegrees;  // char-incomingDegree
        set<char> chars; // record all distinct chars
        queue<char> sources; // zero-degree nodes
        int n = words.size();
        string res = "";
        
        for (int i = 1; i < n; i++) {
            int len1 = words[i - 1].size(), len2 = words[i].size();
            int j = 0;
            for (; j < min(len1, len2); j++) {
                if (words[i - 1][j] == words[i][j]) continue;
                else {
                    graph[words[i - 1][j]].push_back(words[i][j]);
                    indegrees[words[i][j]]++;
                    break; // only record the first different chars
                }
            }
            
            // error, e.g., compaing "abc" and "ab"; space must be smaller than other chars
            if (len1 > len2 && j == len2) return ""; 
        }
        
        for (string s : words) {
            for (char c : s) {
                chars.insert(c);
            }
        }
        for (char c : chars) {
            if (indegrees[c] == 0) sources.push(c);
        }
        
        while (!sources.empty()) {
            char c = sources.front(); sources.pop();
            res += c;
            
            vector<char> children = graph[c];
            for (char child : children) {
                if (--indegrees[child] == 0) sources.push(child);
            }
        }
        
        return (res.size() == chars.size()) ? res : "";
    }
};

// 199. Binary Tree Right Side View
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        if (!root) return {};
        vector<int> res;
        queue<TreeNode*> q({root});
        while (!q.empty()) {
            res.push_back(q.back()->val); // NOTE, back(), add the value of right-most node in last level
            for (int i = q.size(); i > 0; --i) {
                TreeNode * t = q.front(); q.pop();
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
        }
        return res;
    }
};

// 415. Add Strings
// Input: str1='12345', str2='65432'; Output: '77777'
class Solution {
public:
    string addStrings(string str1, string str2) {
        // corner cases
        if (str1.empty() && str2.empty()) return "";
        else if (str1.empty()) return str2;
        else if (str2.empty()) return str1;

        int i = str1.size() - 1, j = str2.size() - 1, curry = 0;
        string res = "";

        // add strings
        while (i >= 0 || j >= 0) { // Time: O(max(len1, len2));  Space: O(1)
            int x = (i >= 0) ? (str1[i--] - '0') : 0;
            int y = (j >= 0) ? (str2[j--] - '0') : 0;
            int val = (x + y + curry) % 10;
            // res.insert(res.begin(), to_string(val)); // insert(): O(N), total O(N^2)
            res += (val + '0');
            curry = (x + y + curry) / 10;  
        }

        if (curry) res += (curry + '0');

        reverse(res.begin(), res.end());  // time, O(N)

        return res;
    }
};












































