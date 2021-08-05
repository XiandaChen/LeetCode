// Throttilng Gateway
// The gateway has the following limits:
// #transactions in any given second cannot exceed 3;
// #transactions in any given 10 second cannot exceed 20; 
// i.e., al requests arrives from any time max(i,T-9) to T (incusive of both) <= 20;
// #transactions in any given minute cannot exceed 60
// Input: [1,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6,7,7]; Output: 2
// In the first second, 4 requests arrives so one is dropped.
// Within 10 seconds, all requests from second 1 to 7, a total of 21 requests arrive.
// The last request (7) is dropped.
int droppedRequest(vector<int> requestTime) {
	int n = requestTime.size(), res = 0;
	for (int i = 0; i < n; ++i) {
		if (i > 2 && (requestTime[i] == requestTime[i-3])) ++ res;
		else if (i > 19 && (requestTime[i] - requestTime[i - 20] < 10)) ++res;
		else if (i > 59 && (requestTime[i] - requestTime[i - 60] < 60)) ++ res;
	}
	return res;
}


// 300. Longest Increasing Subsequence (LIS)
// Input: nums = [10,9,2,5,3,7,101,18]; Output: 4, i.e., [2,3,7,101]
// Method 1: DP, O(n^2), dp[i]=LIS ending with nums[i]; 
// for 0<i<n-1, for 0<j<i, if(nums[j]<nums[i]): dp[i]=max(dp[i],dp[j]+1)
// Method 2: Binary Search, O(nlogn)
class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int> subnums{nums[0]};
        for (int a : nums) {
            if (a < subnums[0]) { // switch the smallest one
                subnums[0] = a;
            }
            else if (a > subnums.back()) { // add larger ones
                subnums.push_back(a);
            }
            else { // change the first num that no-less than a
                int left = 0, right = subnums.size();
                while (left < right) { // binary search
                    int mid = left + (right - left) / 2;
                    if (subnums[mid] < a) left = mid + 1;
                    else right = mid;
                }
                subnums[right] = a;
            }
        }
        return subnums.size();
    }
};

// 818. Race car
// Your car starts at position 0 and speed +1 on an infinite number line.  (Your car can go into negative positions.)
// Instruction "A" (accelerate): position += speed, speed *= 2.
// Instruction "R" (reverse): if your speed is positive then speed = -1 , otherwise speed = 1.  (Your position stays the same.)
// For example, after commands "AAR", your car goes to positions 0->1->3->3, and your speed goes to 1->2->4->-1.
// For some target position, find the length of the shortest sequence of instructions to get there.
// Input: target = 6; Output: 5
// Explanation: The shortest instruction sequence is "AAARA".
// Your position goes from 0->1->3->7->7->6.
class Solution {
public:
    int racecar(int target) {
        int res = 0;
        queue<pair<int, int>> q{{{0, 1}}}; // position-speed
        unordered_set<string> visited{{"0,1"}}; // states: "pos,speed"
        while (!q.empty()) {
            for (int i = q.size(); i > 0; --i) {
                int pos = q.front().first, speed = q.front().second;
                q.pop();
                if (pos == target) return res;

                // instruction accelerate: position += speed, speed *= 2
                int newPos = pos + speed, newSpeed = speed * 2;
                string state = to_string(newPos) + "," + to_string(newSpeed);
                if (!visited.count(state) && 0 < newPos && newPos <= target * 2) {
                    q.push({newPos, newSpeed});
                    visited.insert(state);
                }

                // instruction reverse: position stays the same; 
                // speed is positive then speed = -1 , otherwise speed = 1
                newPos = pos;
                newSpeed = (speed > 0) ? -1 : 1;
                state = to_string(newPos) + "," + to_string(newSpeed);
                if (!visited.count(state) && 0 < newPos && newPos <= target * 2) {
                    q.push({newPos, newSpeed});
                    visited.insert(state);
                }
            }
            ++res;
        }
        return -1;
    }
};


// 130. flipping all 'O's into 'X's in the regions surrounded by 'X'..
class Solution {
public:
    void solve(vector<vector<char> >& board) {
        int n = board.size(), m = board[0].size();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // find all 'O's adjacent to 'O' at the edge
                // temporary set these 'O' to '#'
                if (i == 0 || i == n - 1 || j == 0 || j == m - 1) { 
                    if (board[i][j] == 'O') dfs(board, i, j);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (board[i][j] == 'O') board[i][j] = 'X';
                if (board[i][j] == '#') board[i][j] = 'O';
            }
        }
    }
    void dfs(vector<vector<char>>& board, int i, int j) {
        if (board[i][j] == 'O') {
            board[i][j] = '#'; 
            // inside 'O's that adjacent to 'O' at the edge
            if (0 < i - 1 && board[i - 1][j] == 'O')
                dfs(board, i - 1, j);
            if (i + 1 < board.size() - 1 && board[i + 1][j] == 'O')
                dfs(board, i + 1, j);
            if (0 < j - 1 && board[i][j - 1] == 'O')
                dfs(board, i, j - 1);
            if (j + 1 < board[0].size() - 1 && board[i][j + 1] == 'O')
                dfs(board, i, j + 1);
        }
    }
};


// 772. Basic Calculator III
// contains only non-negative integers, '+', '-', '*', '/' operators, 
// and open '(' and closing parentheses ')'. 
// The integer division should truncate toward zero.
class Solution {
public:
    int calculate(string s) {
        int n = s.size(), num = 0, curRes = 0, res = 0;
        char preOP = '+';
        for (int i = 0; i < n; ++i) {
            char c = s[i];
            if (c >= '0' && c <= '9') {
                num = num * 10 + (c - '0');
            } else if (c == '(') {
                int j = i, cnt = 0;
                for (; i < n; ++i) {
                    if (s[i] == '(') ++cnt;
                    if (s[i] == ')') --cnt;
                    if (cnt == 0) break;
                }
                num = calculate(s.substr(j + 1, i - j - 1));
            }
            if (c == '+' || c == '-' || c == '*' || c == '/' || i == n - 1) {
                switch (preOP) {
                    case '+': curRes += num; break;
                    case '-': curRes -= num; break;
                    case '*': curRes *= num; break;
                    case '/': curRes /= num; break;
                }
                if (c == '+' || c == '-' || i == n - 1) {
                    res += curRes;
                    curRes = 0;
                }
                preOP = c;
                num = 0;
            }
        }
        return res;
    }
};

// Divide N numbers into groups of k elements, such that 
// For each group, numbers[i] <= numbers[i+1]
// Input: N=8, k=4; Output:5, options are [1, 1, 1, 5] [1, 1, 2, 4] [1, 1, 3, 3] [1, 2, 2, 3] [2, 2, 2, 2]
// recursion, O(n^k)
int nToKGroups(int left, int k, int pos, int step) {
    // base case
    if (pos == k) {
        if (left == 0) return 1; // all n divided in K
        else return 0;
    }
    // left==0, then, not guarantee that elem[pos - 1] <= elem[pos] 
    if (left == 0) return 0;
    
    int res = 0;
    for (int i = step; i <= left; ++i) {
        res += nToKGroups(left - i, k, pos + 1, i);
    }
    return res;
}
int nToKGroups (int n, int k) {
    if (n < k) return 0;
    return nToKGroups(n, k, 0, 1);
}
// DP, O(n^2 *k)
// dp[i][j]: number of options to split j numbers into i groups
// initialize: dp[i][i] = char16_t
// dp[i][j] = dp[i-1][j-1] + dp[i][j-i]
// If the first (smallest) element is greater than 1, 
// we can substract 1 from every element and get a valid partition of n-k into k parts, hence P(n-k, k).
// If the first element is equal to 1, 
// the rest form a partition of n-1 into k-1 parts, hence P(n-1, k-1).
int nToKGroups_DP(int n, int k) {
    if (n < k) return 0;
    vector<vector<int>> dp(k + 1, vector<int>(n + 1));

    for (int i = 1; i <= k; ++i) {
        for (int j = i; j <= n; ++j) {
            if (i == j) dp[i][j] = 1;
            else {
                dp[i][j] = dp[i-1][j-1] + dp[i][j-i];
            }
        }
    }
    return dp[k][n];
}

// 239. Sliding Window Maximum
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3; Output: [3,3,5,5,6,7]
// priority_queue, O(NlogN)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;
        priority_queue<pair<int, int>> q; // val-idx, default: max queue
        for (int i = 0; i < n; ++i) {
            while (!q.empty() && q.top().second <= i - k) q.pop();
            q.push({nums[i], i}); // O(logN)
            if (k - 1 <= i) res.push_back(q.top().first);
        }
        return res;
    }
};
// dequeue, O(N)
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> res;
        deque<int> q; // idxs, maintain only useful elements (>=nums[i])
        for (int i = 0; i < n; ++i) {
            if (!q.empty() && q.front() == i - k) q.pop_front();
            while (!q.empty() && nums[q.back()] < nums[i]) q.pop_back();
            q.push_back(i); // log(1)
            if (k - 1 <= i) res.push_back(nums[q.front()]);
        }
        return res;
    }
};

// 139. Word Break
// Input: s = "leetcode", wordDict = ["leet", "code"]
// Output: true; "leetcode" can be segmented as "leet code".
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        const int n = s.size();
        unordered_set<string> wordSet(wordDict.begin(), wordDict.end());
        vector<bool> dp(n + 1);
        dp[0] = true; // true for empty string
        for (int i = 0; i < n + 1; ++i) { // dp.size(), not s.size();
            for (int j = 0; j < i; ++j) {
                // substr from j not j + 1, since dp is 1-based
                if (dp[j] && wordSet.count(s.substr(j, i - j))) { 
                    dp[i] = true; 
					break;
                }
            }
        }
        return dp.back();
    }
};
// 140. Word Break II
// Input: s = "catsanddog", wordDict = ["cat", "cats", "and", "sand", "dog"]
// Output: ["cats and dog", "cat sand dog"]
class Solution {
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_map<string, vector<string>> m; // string -- list of breaked words
        return wordBreak(s, wordDict, m);
    }
    vector<string> wordBreak(string s, vector<string>& wordDict, unordered_map<string, vector<string>>& m) {
        if (s.empty()) return {""};
        if (m.count(s)) return m[s];
        vector<string> res;
        for (auto word : wordDict) { // for all cases that s contains word at the begining
            if (s.substr(0, word.size()) != word) continue; 
            vector<string> remains = wordBreak(s.substr(word.size()), wordDict, m);
            for (auto str : remains) {
                res.push_back(word + (str.empty() ? "" : " " + str));
            }
        }
        return m[s] = res;
    }
};

// 200. Number of Islands
// Input: grid = [
//	  ["1","1","0","0","0"],
//	  ["1","1","0","0","0"],
//	  ["0","0","0","1","1"],
//	  ["0","1","0","1","1"]]
// Output: 3
class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size(), res = 0;
        vector<vector<bool>> visited(n, vector<bool>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == '1' && !visited[i][j]) {
                    ++res;
                    dfs(grid, visited, i, j);
                }
            }
        }
        return res;
    }
    void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j) {
        if (i < 0 || i >= grid.size() 
            || j < 0 || j >= grid[0].size() 
           || grid[i][j] == '0' || visited[i][j]) return;
        visited[i][j] = true;
        dfs(grid, visited, i + 1, j);
        dfs(grid, visited, i - 1, j);
        dfs(grid, visited, i, j + 1);
        dfs(grid, visited, i, j - 1);
    }
};
// 694. Number of Distinct Islands
// Input: grid = [11011
//				  10000
//				  00001
//				  11011]
// Output: 3
class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        unordered_set<string> islands; // island patterns
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    set<string> nodes;
                    dfs(grid, visited, i, j, i, j, nodes);
                    string island = "";
                    for (auto n : nodes) { // encoding the island
                        island += n + "_";
                    }
                    islands.insert(island);
                }
            }
        }
        return islands.size();
    }
    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, 
             int x0, int y0, int i, int j, set<string>& nodes) {
        if (i < 0 || i >= grid.size()
           || j < 0 || j >= grid[0].size()
           || grid[i][j] == 0 || visited[i][j]) return;
        
        visited[i][j] = true;
        nodes.insert(to_string(i - x0) + "_" + to_string(j - y0)); // relative dist to upleft node
        
        dfs(grid, visited, x0, y0, i + 1, j, nodes);
        dfs(grid, visited, x0, y0, i - 1, j, nodes);
        dfs(grid, visited, x0, y0, i, j + 1, nodes);
        dfs(grid, visited, x0, y0, i, j - 1, nodes);
    }
};

// 836. Rectangle Overlap
// Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]; Output: true
class Solution {
public:
    bool isRectangleOverlap(vector<int>& rec1, vector<int>& rec2) {
        return min(rec1[2], rec2[2]) > max(rec1[0], rec2[0]) 
			&& min(rec1[3], rec2[3]) > max(rec1[1], rec2[1]);
    }
};
// 223. Rectangle Area
// Input: rec1 = [0,0,2,2], rec2 = [1,1,3,3]; Output: 1
class Solution {
public:
    int computeArea(ivector<int>& rec1, vector<int>& rec2) {
        int area1 = (rec1[2] - rec1[0]) * (rec1[3] - rec1[1]);
		int area2 = (rec2[2] - rec2[0]) * (rec2[3] - rec2[1]);
        if (rec1[2] <= rec2[0] || rec1[3] <= rec2[1] 
			|| rec2[2] <= rec1[0] || rec2[3] <= rec1[1]) 
            return area1 + area2;
        return area1 - ((min(rec2[2], rec1[2]) - max(rec1[0], rec2[0])) * (min(rec1[3], rec2[3]) - max(rec1[1], rec2[1]))) + area2;
    }
};




















