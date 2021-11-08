// 323. Number of Connected Components in an Undirected Graph
class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);
        int res = 0;
        
        // adjacent list
        for (auto & a: edges) {
            graph[a[0]].push_back(a[1]);
            graph[a[1]].push_back(a[0]);
        }
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                res++;
                dfs(graph, visited, i);
            }
        }
        
        return res;
    }
    
    void dfs(vector<vector<int>> & graph, vector<bool> & visited, int i) {
        if (visited[i]) return;
        visited[i] = true;
        for (auto & a: graph[i])
            dfs(graph, visited, a);
    }
};

// 370. Range Addition, Time O(k+n), Space O(1)
// Input: length = 5, updates = [[1,3,2],[2,4,3],[0,2,-2]]
// after updates, nums = [-2, 2, 3, 2, -2, -3], accumulate sum are the output
// Output: [-2,0,3,5,3]
class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> res, nums(length + 1, 0); // length+1: in case idx (end+1)==length
        
        // updates[i] = [startIdx_i, endIdx_i, inc_i]
        // nums[startIdx_i, endIdx_i] += inc_i; and then nums[startIdx_i+1,:] -= inc_i
        for (auto & a: updates) {
            nums[a[0]] += a[2];  // accumulate sum from startIdx_i will add inc_i to [startIdx_i, :]
            nums[a[1] + 1] -= a[2]; // accumulate sum from startIdx_i+1 will remove inc_i from [startIdx_i+1, :]
        }
        
        int sum = 0;
        for (int i = 0; i < length; ++i) {
            sum += nums[i];
            res.push_back(sum);
        }
        
        return res;
    }
};

// 1041. Robot Bounded In Circle
// The robot stays in the circle iff (looking at the final vector) it changes direction 
// (ie. doesn't stay pointing north), or it moves 0.
class Solution {
public:
    bool isRobotBounded(string instructions) {
        int face = 0; // 0-north, 1-east, 2-south, 3-west
        vector<vector<int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // 0-north, 1-east, 2-south, 3-west
        vector<int> cur = {0, 0};
        for (char c : instructions) {
            if (c == 'G') {
                cur = {cur[0] + dirs[face][0], cur[1] + dirs[face][1]};
            }
            else if (c == 'L') {
                face = (face + 4 - 1) % 4; // +4 : in case negatives
            }
            else {
                face = (face + 1) % 4;
            }
        }
        // circle: if returns to (0,0), or face other direction other initial north
        return (cur[0] == 0 && cur[1] == 0) || face != 0;
    }
};

// 829. Consecutive Numbers Sum
// Input: n = 9; Output: 3; Explanation: 9 = 4 + 5 = 2 + 3 + 4
// N = x + (x+1) + (x+2) +...+(x+k-1) = kx + (k-1)k/2
// ==> x = (N - (k-1)k/2) / k > 0 ==> N - (k-1)k/2 > 0 ==> k < sqrt(2*N)
class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int res = 1; // the array of [n]
        for (int k = 2; k < sqrt(2 * n); k++) { // array of length k
            if ((n - k * (k - 1) / 2) % k == 0) res++;
        }
        return res;
    }
};

// 937. Reorder Data in Log Files
// Input: logs = ["dig1 8 1 5 1","let1 art can","dig2 3 6","let2 own kit dig","let3 art zero"]
// Output: ["let1 art can","let3 art zero","let2 own kit dig","dig1 8 1 5 1","dig2 3 6"]
class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> res, digitLogs;
        vector<vector<string>> letterLogs; // {identifier, contents}
        
        for (string log: logs) {
            auto pos = log.find(" ");
            if (isdigit(log[pos + 1])) {
                digitLogs.push_back(log); continue;
            }
            letterLogs.push_back({log.substr(0, pos), log.substr(pos + 1)});
        }
        
        // sorted lexicographically by their contents. 
        // for same contents, then sort them lexicographically by their identifiers.
        auto cmp = [](vector<string> &a, vector<string> &b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
        };
        sort(letterLogs.begin(), letterLogs.end(), cmp);
        
        for (auto &a : letterLogs) {
            res.push_back(a[0] + " " + a[1]);
        }
        
        // digit-logs maintain their relative ordering.
        for (auto &a : digitLogs) {
            res.push_back(a);
        }
        
        return res;
    }
};

// 909. Snakes and Ladders
// the cells are labeled from 1 to n2 in a Boustrophedon style 
// starting from the bottom left of the board (i.e. board[n - 1][0]) 
// and alternating direction each row.
class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size(), res = 0;
        vector<int> visited(n * n + 1); // board idx: [1, n^2]
        queue<int> q{{1}}; // BFS, starting from bottom-left
        
        while (!q.empty()) {
            for (int i = q.size(); i > 0; i--) {
                int idx = q.front(); q.pop();
                
                if (idx == n * n) return res; // reach the end
                
                for (int j = 1; j <= 6 && idx + j <= n * n; j++) { // 6-sided die
                    vector<int> pos = getPosition(n, idx + j); // NOTE, idx+j
                    // if pos has ladder or not
                    int next = board[pos[0]][pos[1]] == -1 ? (idx + j) : board[pos[0]][pos[1]];
                    
                    if (visited[next]) continue;
                    
                    visited[next] = true;
                    q.push(next);
                }
            }
            res++;
        }
        
        return -1; 
    }
    
    // from 1 to n^2 in a Boustrophedon style 
    vector<int> getPosition(int n, int idx) { 
        int x = (idx - 1) / n, y = (idx - 1) % n; // board idx: [1, n^2]
        if (x % 2 == 1) { // odd row (e.g., 1th), alternating direction from right
            y = n - 1 - y;
        }
        // NOTE, must after changing y if needed
        x = n - 1 - x; // starting from the bottom left of the board (i.e. board[n - 1][0]) 
        return {x, y};
    }
};

// 1152. Analyze User Website Visit Pattern
class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        unordered_map<string, map<int, string>> userData; // user-<time, web>, map sorted by time
        unordered_map<string, int> sequenceCount; // pattern-cnt
        int n = username.size(), maxCount = 0;
        string res = "";
        
        // user visit logs
        for (int i = 0; i < n; i++) {
            userData[username[i]][timestamp[i]] = website[i];
        }
        
        // collect pattern, i.e., three sequence
        for (auto data : userData) {
            unordered_set<string> sequences; // set to remove duplicates
            for (auto it1 = data.second.begin(); it1 != data.second.end(); it1++) {
                for (auto it2 = next(it1); it2 != data.second.end(); it2++) {
                    for (auto it3 = next(it2); it3 != data.second.end(); it3++) {
                        sequences.insert(it1->second + "$" + it2->second + "#" + it3->second);
                    }
                }
            }
            
            for (auto seq: sequences) sequenceCount[seq]++;
        }
        
        // find sequence with longest count
        for (auto seq : sequenceCount) {
            if (res == "" || seq.second > maxCount) {
                res = seq.first;
                maxCount = seq.second;
            }
            else if (seq.second == maxCount) {
                res = min(res, seq.first);
                maxCount = seq.second;
            }
        }
        
        auto pos1 = res.find("$");
        auto pos2 = res.find("#");
        
        return {res.substr(0, pos1), res.substr(pos1 + 1, pos2 - pos1 - 1), res.substr(pos2 + 1)};
    }
};

// 1010. Pairs of Songs With Total Durations Divisible by 60
class Solution {
public:
    int numPairsDivisibleBy60(vector<int>& time) {
        vector<int> remainder(60, 0);
        int res = 0;
        for (int t : time) {
            if (t % 60 == 0) {
                res += remainder[0];
            }
            else {
                res += remainder[60 - t % 60];
            }
            remainder[t % 60]++;
        }
        return res;
    }
};

// 696. Count Binary Substrings
// Input: s = "00110011"; Output: 6; Explanation: "0011", "01", "1100", "10", "0011", and "01".
class Solution {
public:
    int countBinarySubstrings(string s) {
        int n = s.size(), zeros = 0, ones= 0, res = 0;
        
        if (s[0] == '0') zeros++;
        else ones++;
        
        for (int i = 1; i < n; i++) {
            if (s[i] == '0') {
                zeros = (s[i - 1] == '0') ? zeros + 1 : 1;
                if (ones >= zeros) res++;
            }
            else if (s[i] == '1') {
                ones = (s[i - 1] == '1') ? ones + 1 : 1;
                if (zeros >= ones) res++;
            }
        }
        
        return res;
    }
};

// 1268. Search Suggestions System
// Input: products = ["mobile","mouse","moneypot","monitor","mousepad"], searchWord = "mouse"
// Output: [["mobile","moneypot","monitor"],
// ["mobile","moneypot","monitor"],
// ["mouse","mousepad"],
// ["mouse","mousepad"],
// ["mouse","mousepad"]]
class Trie {
public:
    struct TrieNode {
        TrieNode * child[26];
        bool isWord;
        TrieNode () : isWord(false) {
            for (auto &a : child) a = nullptr;
        }
    };
    
    Trie() {root = new TrieNode();}
    
    void insert(string & s) {
        TrieNode * p = root;
        for (char & c : s) {
            if (!p->child[c - 'a']) p->child[c - 'a'] = new TrieNode();
            p = p->child[c - 'a'];
        }
        p->isWord = true;
    }
    
    void dfsPrefix(TrieNode * p, string & word, vector<string> & res) {
        if (res.size() == 3) return;  // return the three lexicographically minimums products.
        if (p->isWord) res.push_back(word);
        // dfs to check all possible paths
        for (char c = 'a'; c <= 'z'; c++) {
            if (p->child[c - 'a']) {
                word.push_back(c);
                dfsPrefix(p->child[c - 'a'], word, res);
                word.pop_back();
            }
        }
    }
    
    vector<string> getWordsWithPrefix(string & prefix) {
        TrieNode * p = root;
        vector<string> res;
        for (char & c : prefix) {
            if (!p->child[c - 'a']) return res;
            p = p->child[c - 'a'];
        }
        dfsPrefix(p, prefix, res);
        return res;
    }

private:
    TrieNode * root;
};

class Solution {
public:
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        vector<vector<string>> res;
        Trie * trie = new Trie();
        for (string s : products) trie->insert(s);
        
        string prefix = "";
        for (char &c : searchWord) {
            prefix += c;
            res.push_back(trie->getWordsWithPrefix(prefix));
        }
        return res;
    }
};

// 1710. Maximum Units on a Truck
// Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
// Output: (1 * 3) + (2 * 2) + (1 * 1) = 8.
class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        auto cmp = [](vector<int> &a, vector<int> &b) {
            return a[1] > b[1]; // descending
        };
        sort(boxTypes.begin(), boxTypes.end(), cmp); // sort descending by unit
        
        int res = 0, n = boxTypes.size();
        for (int i = 0; i < n; i++) {
            int boxs = boxTypes[i][0], unit = boxTypes[i][1];
            
            while (truckSize > 0 && boxs > 0) {
                res += unit;
                boxs--;
                truckSize--;
                if (boxs <= 0 || truckSize <= 0) break;
            }
            
            if (truckSize <= 0) return res;
            
        }
        return res;
    }
};

// 994. Rotting Oranges; 0-empty cell, 1-fresh orange, 2-rotten orange
// Return the minimum number of minutes that must elapse until no cell has a fresh orange. 
// If this is impossible, return -1.
// Input: grid = [[2,1,1],[1,1,0],[0,1,1]]; Output: 4
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int res = 0, m = grid.size(), n = grid[0].size(), freshCnt = 0;
        queue<pair<int, int>> q; // bfs: row-col
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) freshCnt++;
                else if (grid[i][j] == 2) q.push({i, j}); // rotten orange
            }
        }
        
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        while (!q.empty() && freshCnt > 0) { // NOTE, freshCnt > 0
            for (int i = q.size(); i > 0; i--) {
                auto a = q.front(); q.pop();
                for (int k = 0; k < 4; k++) {
                    int row = a.first + dirs[k][0], col = a.second + dirs[k][1];
                    if (row >= 0 && row < m && col >= 0 && col < n
                       && grid[row][col] == 1) {
                        freshCnt--;
                        grid[row][col] = 2;
                        q.push({row, col});
                    }
                }
            }
            res += 1;
        }
        
        return freshCnt == 0 ? res : -1;
    }
};

// 1465. Maximum Area of a Piece of Cake After Horizontal and Vertical Cuts
// Input: h = 5, w = 4, horizontalCuts = [3,1], verticalCuts = [1]; Output: 6
class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        
        const int mod=1e9+7;
        int m = horizontalCuts.size(), n = verticalCuts.size();
        int maxHeight = horizontalCuts[0], maxWidth = verticalCuts[0];
        
        for (int i = 1; i < m; i++) 
            maxHeight = max(maxHeight, horizontalCuts[i] - horizontalCuts[i - 1]);
        maxHeight = max(maxHeight, h - horizontalCuts[m - 1]);
        
        for (int i = 1; i < n; i++) 
            maxWidth = max(maxWidth, verticalCuts[i] - verticalCuts[i - 1]);
        maxWidth = max(maxWidth, w - verticalCuts[n - 1]);
        
        // in case h=1000000000, w=1000000000, [2], [2]
        long long int mH = maxHeight, mW = maxWidth;  
        
        return (mH * mW) % mod;
    }
};

//  547. Number of Provinces
// Input: isConnected = [[1,1,0],[1,1,0],[0,0,1]]; Output: 2
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size(), res = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                res++;
                helper(isConnected, visited, i);
            }
        }
        return res;
    }
    void helper(vector<vector<int>>& isConnected, vector<bool> & visited, int i) {
        visited[i] = true;
        for (int k = isConnected.size() - 1; k >= 0; k--) {
            if (visited[k] || isConnected[k][i] == 0) continue;
            helper(isConnected, visited, k);
        }
    }
};

// 1167. Minimum Cost to Connect Sticks
// Input: sticks = [2,4,3]; Output: 14 = (2+3=5) + (5+4=9)
class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        if (sticks.size() < 2) return 0;
        
        priority_queue<int, vector<int>, greater<int>> q;
        
        for (int s : sticks) q.push(s);
        
        int res = 0;
        while (q.size() > 1) {
            int a = q.top(); q.pop();
            int b = q.top(); q.pop();
            int c = a + b;
            res += c;
            q.push(c);
        }
        
        return res;
    }
};

// 472. Concatenated Words
class Solution {
public:
    vector<string> findAllConcatenatedWordsInADict(vector<string>& words) {
        if (words.size() <= 2) return {};
        
        unordered_set<string> wordSet(words.begin(), words.end());
        vector<string> res;
        
        for (string word : words) { // NOTE, words, not wordSet
            // concatenated word: at least two shorter words 
            wordSet.erase(word);
            int len = word.size();
            if (len == 0) continue;
            
            vector<bool> dp(len + 1, false); // dp[i]: word[0:i] is concatenatable
            dp[0] = true;
            for (int i = 0; i < len + 1; i++) {
                for (int j = 0; j < i; j++) {
                    if (dp[j] && wordSet.count(word.substr(j, i - j))) {
                        dp[i] = true;
                        break;
                    }
                }
            }
            
            if (dp.back()) res.push_back(word);
            wordSet.insert(word);
        }
        
        return res;
    }
};

// 1492. The kth Factor of n
class Solution {
public:
    int kthFactor(int n, int k) {
        vector<int> factors;
        int sqrtN = (int) sqrt(n);
        for (int i = 1; i <= sqrtN; i++) { // O(sqrt(N))
            if (n % i == 0) {
                factors.push_back(i);
                k--;
                if (k == 0) return i;
            }
        }
        // if n is perfect square, skip duplicate in factors
        // n=16,k=5: 1, 2, 4, 8, 16
        // factors=[1, 2, 4] , k=(5-3)+1=3, [nDiv - k]=[0]
        if (sqrtN * sqrtN == n) k++;
        int nDiv = factors.size();
        return (k <= nDiv) ? n / factors[nDiv - k] : -1;
        
        // for (int i = 1; i <= n; i++) { // O(N)
        //     if (n % i == 0) k--;
        //     if (k == 0) return i;
        // }
        // return -1;
    }
};

// 907. Sum of Subarray Minimums
// Input: arr = [3,1,2,4]; Output: 17
// Explanation: Subarrays are [3], [1], [2], [4], [3,1], [1,2], [2,4], [3,1,2], [1,2,4], [3,1,2,4]. 
// Minimums are 3, 1, 2, 4, 1, 1, 2, 1, 1, 1.; Sum is 17.
// class Solution {
// public:
//     int sumSubarrayMins(vector<int>& arr) {
//         int n = arr.size(), res = arr[0], Mod = 1e9 + 7; // NOTE, res = arr[0]
//         vector<int> dp(n); // dp[i]: sum of subarray minimus where subarrays end with arr[i]
//         dp[0] = arr[0];
//         for (int i = 1; i < n; i++) {
//             if (arr[i] >= arr[i - 1]) {
//                 dp[i] = dp[i - 1] + arr[i];
//             }
//             else { // [2, 3, 1]=>[[2,3,1], [3,1], [1]]
//                 int j = i - 1;
//                 while (j >= 0 && arr[j] > arr[i]) j--;  // O(N^2), time limited exceeded
//                 dp[i] = (j < 0) ? (i + 1) * arr[i] : (dp[j] + (i - j) * arr[i]);
//             }
//             res = (res + dp[i]) % Mod;
//         }
//         return res;
//     }
// };
class Solution {
public:
    int sumSubarrayMins(vector<int>& arr) {  // O(N)
        int res = 0, n = arr.size(), Mod = 1e9 + 7;
        stack<int> st{{-1}}; // monotonic stack, ascending order
        vector<int> dp(n + 1); // dp[i]: sum of subarray minimus where subarrays end with arr[i-1]
        for (int i = 0; i < n; i++) {
            while (st.top() != -1 && arr[i] <= arr[st.top()]) st.pop();
            dp[i + 1] = (dp[st.top() + 1] + (i - st.top()) * arr[i]) % Mod;
            st.push(i);
            res = (res + dp[i + 1]) % Mod;  // NOTE, dp[i+1]
        }
        return res;
    }
};

// 1192. Critical Connections in a Network
// Input: n = 4, connections = [[0,1],[1,2],[2,0],[1,3]]; Output: [[1,3]]
class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // time: dfs access orders, low: lowest time among all accessable nodes
        vector<int> time(n), low(n); 
        unordered_map<int, vector<int>> graph;
        vector<vector<int>> res;
        int cnt = 1; // dfs access nodes naming cnt from 1
        
        for (auto con : connections) {
            graph[con[0]].push_back(con[1]);
            graph[con[1]].push_back(con[0]);
        }
        
        helper(graph, -1, 0, cnt, time, low, res);
        return res;
    }
    
    void helper(unordered_map<int, vector<int>> & graph, int pre, int cur, int cnt, 
               vector<int> & time, vector<int> & low, vector<vector<int>> & res) {
        time[cur] = low[cur] = cnt++;
        for (int next : graph[cur]) {
            if (time[next] == 0) { // dfs access, and update low[cur]
                helper(graph, cur, next, cnt, time, low, res);
                low[cur] = min(low[cur], low[next]); // NOTE, min(low, low)
            }
            else if (next != pre) { // NOTE, must check (next != pre)
                low[cur] = min(low[cur], time[next]);
            }
            // critical edge
            if (low[next] > time[cur]) res.push_back({cur, next});
        }
    }
};

// 992. Subarrays with K Different Integers
// Input: nums = [1,2,1,2,3], k = 2; Output: 7
// Explanation: [1,2], [2,1], [1,2], [2,3], [1,2,1], [2,1,2], [1,2,1,2]
class Solution {
public:
    int subarraysWithKDistinct(vector<int>& nums, int k) {
        // (subarrays with at most K distinct num) - (subarrays with at most K-1 distinct num)
        return helper(nums, k) - helper(nums, k - 1);
    }
    // subarrays with at most K distinct num
    int helper(vector<int>& nums, int k) {
        int n = nums.size(), left = 0, res = 0;
        unordered_map<int, int> numCnt; // number-count
        for (int i = 0; i < n; i++) {
            if (numCnt[nums[i]] == 0) k--; // k-- if adding new nums[i] to subarray
            numCnt[nums[i]]++;
            while (k < 0) { // sliding window
                if (--numCnt[nums[left]] == 0) k++;
                left++;
            }
            res += i - left + 1;  // count the valid subarrays
        }
        return res;
    }
};

// 828. Count Unique Characters of All Substrings of a Given String
// Input: s = "ABC"; Output: 10
// Explanation: All possible substrings are: "A","B","C","AB","BC" and "ABC".
// Sum of lengths of all substring is 1 + 1 + 1 + 2 + 2 + 3 = 10
class Solution {
public:
    int uniqueLetterString(string s) {
        int n = s.size(), res = 0;
        for (int i = 0; i < n; i++) {
            int j = i - 1, k = i + 1;
            while (j >= 0 && s[j] != s[i]) j--;
            while (k < n && s[k] != s[i]) k++;
            res += (i - j) * (k - i); // (i-j)*(k-i): #substrings that s[i] appears
        }
        return res;
    }
}

// 1648. Sell Diminishing-Valued Colored Balls
// Input: inventory = [2,5], orders = 4;  Output: 14
// Explanation: Sell the 1st color 1 time (2) and the 2nd color 3 times (5 + 4 + 3).
// The maximum total value is 2 + 5 + 4 + 3 = 14.
// priority_queue sell one by one: O(klogn) time limit exceeded
// inventory = [1000000000], orders = 1000000000
#define ull unsigned long long
const int mod = 1e9 + 7;
class Solution {
public:
    int maxProfit(vector<int>& inventory, int orders) {
        priority_queue<int> q(inventory.begin(), inventory.end()); // maxHeap
        long res = 0, sameBalls = 1; // sameBalls: num balls having the same max value
        
        while (orders > 0) {
            int t = q.top(); q.pop();
            // except sameBalls, may need other balls to server the orders
            if (!q.empty() && (t - q.top()) * sameBalls <= orders) { // 
                res = (res + summation(q.top() + 1, t) * sameBalls) % mod;
                orders -= (t - q.top()) * sameBalls;
            }
            else { // sameBalls can server the orders
                int x = orders / sameBalls; // each sameBalls serve x orders
                int y = orders % sameBalls;  // remaining orders after serving x*sameBalls orders
                ull b = t - x; // value for each sameBalls after serving x orders
                res = (res + summation(b + 1, t) * sameBalls) % mod; // [t, t-1,..,b+1] for each sameBalls
                res = (res + b * y) % mod; // one ball (value of b) for each orders (y)
                break;
            }
            sameBalls++;
        }
        
        
        return res;
    }
    
    // sum of [b, b+1, ..., e]
    ull summation(ull b, ull e) { // b: begin, e: end of the array
        ull m = b + e, n = e - b + 1;  // m: sum of the begin and end elem, n: num of elems
        return m * n / 2 % mod; // m * n may overflow int
    };
};

// 926. Flip String to Monotone Increasing
// Input: s = "010110"; Output: 2
// Explanation: We flip to get 011111, or alternatively 000111.
class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n = s.size(), res = INT_MAX;
        // cnt1[i]: num flipping 1 to 0 in s[0:i-1] to make monotone increasing
        // cnt2[j]: num flipping 0 to 1 in s[j:n-1] to make monotone increasing
        vector<int> cnt1(n + 1), cnt2(n + 1);
        
        for (int i = 1, j = n - 1; j >= 0; i++, j--) {
            cnt1[i] = cnt1[i - 1] + ((s[i - 1] == '1') ? 1 : 0);
            cnt2[j] = cnt2[j + 1] + ((s[j] == '0') ? 1 : 0);
        }
        // at some pos, (cnt1[i] + cnt2[i]) get minimum flippings
        for (int i = 0; i <= n; i++) res = min(res, cnt1[i] + cnt2[i]);
        
        return res;
    }
};

// 454. 4Sum II
// 0 <= i, j, k, l < n
// nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0

class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> m; // complement fo 2sum - count
        int res = 0;
        
        for (int i = (int)nums1.size() - 1; i >= 0; i--) {
            for (int j = (int)nums2.size() - 1; j >= 0; j--) {
                m[nums1[i] + nums2[j]]++;
            }
        }
        
        for (int i = (int)nums3.size() - 1; i >= 0; i--) {
            for (int j = (int)nums4.size() - 1; j >= 0; j--) {
                int target = -1 * (nums3[i] + nums4[j]);
                res += m[target];
            }
        }
        
        return res;
    }
};

// 490. The Maze
// The ball can go through the empty spaces by rolling up, down, left or right, 
// but it won't stop rolling until hitting a wall.
// Input: maze = [[0,0,1,0,0],[0,0,0,0,0],[0,0,0,1,0],[1,1,0,1,1],[0,0,0,0,0]], 
// start = [0,4], destination = [4,4]; Output: true
// Explanation: One possible way is : left -> down -> left -> down -> right -> down -> right.
class Solution {
public:
    vector<vector<int>> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        return helper(maze, start[0], start[1], destination[0], destination[1]);
    }
    
    bool helper(vector<vector<int>>& maze, int i, int j, int di, int dj) {
        if (i == di && j == dj) return true; // the ball stops at the destination
        maze[i][j] = -1; // memoization, [i][j] has been visited
        
        int m = maze.size(), n = maze[0].size();
        bool res = false;
        
        for (auto dir : dirs) {
            int x = i, y = j;
            while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] != 1) {
                x += dir[0]; y += dir[1]; // keep going until reaching wall
            }
			// trace back to previous empty space, i.e., where the ball stops
            x -= dir[0]; y -= dir[1];  
            
            if (maze[x][y] != -1) { //[x][y] is empty space and have not been visited yet
                res |= helper(maze, x, y, di, dj); // dfs
            }
        }
        
        return res;
    }
};

// 1628. Design an Expression Tree(for postfix) With Evaluate Function
// Input: s = ["3","4","+","2","*","7","/"]
// Output: 2; ((3+4)*2)/7) = 14/7 = 2.
/**
 * This is the interface for the expression tree Node.
 * You should not remove it, and you can define some classes to implement it.
 */
class Node {
public:
    virtual ~Node () {};
    virtual int evaluate() const = 0;
protected:
    // define your fields here
};
class NumNode : public Node {
public:
    NumNode(int val) : val(val) {}
    int evaluate() const {return val;}
protected:
    int val;
};
class OpNode : public Node {
public:
    OpNode(char op, Node * left, Node * right) : op(op), left(left), right(right) {}
    int evaluate() const;
protected:
    char op;
    Node * left, * right;
};
int OpNode::evaluate() const {
    switch(this->op) {
        case '+': return this->left->evaluate() + this->right->evaluate();
        case '-': return this->left->evaluate() - this->right->evaluate();
        case '*': return this->left->evaluate() * this->right->evaluate();
        case '/': return this->left->evaluate() / this->right->evaluate();
        default: return 0;
    }
}
/**
 * This is the TreeBuilder class.
 * You can treat it as the driver code that takes the postinfix input 
 * and returns the expression tree represnting it as a Node.
 */
class TreeBuilder {
public:
    Node* buildTree(vector<string>& postfix) {
        stack<Node*> st;
        for (string s : postfix) {
            if (isdigit(s[0])) {
                st.push(new NumNode(stoi(s)));
            }
            else {
                auto right = st.top(); st.pop();
                auto left = st.top(); st.pop();
                st.push(new OpNode(s[0], left, right));
            }
        }
        return st.top();
    }
};

// 1135. Connecting Cities With Minimum Cost (min spanning tree)
// Input: n = 3, connections = [[1,2,5],[1,3,6],[2,3,1]]
// Output: 6; Choosing any 2 edges will connect all cities with the minimum 2.
class Solution { // MST: Prim's algorithm, O((E+N)logN)
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        unordered_map<int, vector<pair<int, int>>> graph; // x-<cost, y>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; // minHeap:cost
        vector<int> minCost(n + 1, INT_MAX); // Prim's: minCost[v] = min(minCost[v], cost(u,v));
        vector<bool> visited(n + 1, false);
        int numVisited = 0, res = 0;
        
        for (auto & a : connections) {
            graph[a[0]].push_back({a[2], a[1]});
            graph[a[1]].push_back({a[2], a[0]});
        }
        
        q.push({0, 1});  // N: 1 to N
        
        while (numVisited < n && !q.empty()) {
            int cost = q.top().first, city = q.top().second;
            q.pop();
            if (visited[city]) continue;
            visited[city] = true;
            numVisited++;
            res += cost;
            for (auto & a : graph[city]) { // level-order
                cost = a.first; city = a.second;
                if (!visited[city] && cost < minCost[city]) {
                    minCost[city] = cost;
                    q.push({cost, city});
                }
            }
        }
        
        return numVisited == n ? res : -1;
    }
};

// 1915. Number of Wonderful Substrings
// A wonderful string: at most one letter appears an odd number of times.
// Given a string word that consists of the first ten lowercase letters ('a' through 'j'),
// Similar idea: Subarray sum equals K
using ll = long long;
class Solution {
public:
    long long wonderfulSubstrings(string word) {
        // substring is encoded as bitmask state
        // ith bit of bitmask is 1/0 -> ith char present odd/even times
        unordered_map<int, ll> mp; // substring state - count
        
        mp[0] = 1; // NOTE, must
        ll state = 0, res = 0;  // NOTE, ll, not int
        
        for (char & c : word) {
            // state for substring [0,i]
            state ^= (1 << (c - 'a')); // flip ith bit of state for substring [0,i-1]
            
            // case 1: all chars between substring [j+1, i] present even times 
            // that is, find pos j such that state[0,j] == state[0,i]
            res += mp[state];
            
            // case 2: only one char between substring [j+1, i] presents odd times
            // that is, find pos j such that state[0,j] only diff from state[0,i] at one bit
            // for example, for 'a', state[0,j]='0101010101', state[0,i]='0101010100'
            for (char p = 'a'; p <= 'j'; p++) {
                int tmp_state = state ^ (1 << (p - 'a'));
                res += mp[tmp_state];
            }
            
            mp[state]++;
        }
        
        return res;
    }
};

// 1730. Shortest Path to Get Food
// BFS gurantees to find the minimum number of steps in a grid!
class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<vector<int>> q; // <i, j>
        
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '*') { // starting position
                    q.push({i, j}); 
                    break;
                }
            }
        }
        
        int step = 0;
        while (!q.empty()) {
            step++;
            for (int i = q.size(); i > 0; i--) {
                auto cur = q.front(); q.pop();
                for (auto dir : dirs) {
                    int x = cur[0] + dir[0], y = cur[1] + dir[1];
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 'X') continue;
                    if (grid[x][y] == '#') return step; // found the target
                    grid[x][y] = 'X'; // [x][y] has been visited
                    q.push({x, y});
                }
            }
        }
        
        return -1;
    }
};

// 1120. Maximum Average Subtree
class Solution {
public:
    double maximumAverageSubtree(TreeNode* root) {
        int nodeNum = 0, nodeVal = 0;
        double res = 0;
        helper(root, nodeNum, nodeVal, res);
        return res;
    }
    void helper(TreeNode * cur, int & nodeNum, int & nodeVal, double & maxAvg) {
        if (!cur) return ;
        if (!cur->left && !cur->right) { // left node, break recursion
            nodeNum = 1;
            nodeVal = cur->val;
            maxAvg = max(maxAvg, nodeVal * 1.0 / nodeNum);
            return ;
        }
        
        int lnum = 0, lval = 0, rnum = 0, rval = 0; // NOTE, initiaze =0
        helper(cur->left, lnum, lval, maxAvg);
        helper(cur->right, rnum, rval, maxAvg);
        nodeNum = lnum + rnum + 1;
        nodeVal = lval + rval + cur->val;
        maxAvg = max(maxAvg, nodeVal * 1.0 / nodeNum);
    }
};

// 1973. Count Nodes Equal to Sum of Descendants
class Solution {
public:
    int equalToDescendants(TreeNode* root) {
        int res = 0;
        treeSum(root, res);
        return res;
    }
    // sum of the tree rooted at node
    long long treeSum(TreeNode * node, int & res) {
        if (!node) return 0;
        long long lsum = treeSum(node->left, res);
        long long rsum = treeSum(node->right, res);
        if ((lsum + rsum) == node->val) res++;
        return (lsum + rsum + node->val);
    }
};

// 1151. Minimum Swaps to Group All 1's Together
// Input: data = [1,0,1,0,1,0,0,1,1,0,1]
// Output: 3; One possible solution is [0,0,0,0,0,1,1,1,1,1,1].
class Solution {
public:
    int minSwaps(vector<int>& data) {
        int n = data.size();
        
        // step 1: Count how many 1 in the data and set this number as the size of sliding window.
        int window = accumulate(data.begin(), data.end(), 0);
        
        if (window == 0 || window == n) return 0; // not need to swap
        
        // ones: num of ones in subwindow [0, window]
        // step 2: count how many 0 in the sliding window.
        int ones = accumulate(data.begin(), data.begin() + window, 0);
        int zeros = window - ones;
        
        // step 3: Shift the sliding window and choose the sliding window with the minimum 0 count.
        int left = 0, right = window, res = zeros;
        while (right < n) {
            zeros -= !data[left++]; // 
            zeros += !data[right++];
            if (zeros < res) res = zeros;
        }
        
        return res;
    }
};

// 315. Count of Smaller Numbers After Self
// Input: nums = [5,2,6,1]; Output: [2,1,1,0]
class Solution {    
public:
    vector<int> countSmaller(vector<int>& nums) {        
        int n = nums.size();
        if (n == 0) return {};
        
        vector<int> sortedNums = nums;        
        vector<int> counts(n,0);
        DivideConque(nums,sortedNums, counts, 0, n - 1); 
        return counts;
    }
    
    void DivideConque(vector<int>& nums, vector<int>& sortedNums, 
                      vector<int>& counts, int start, int end){
        if (start == end) return;
        
        // divide: sort each part
        int mid = start + (end - start) / 2;
        DivideConque(nums, sortedNums, counts, start, mid);
        DivideConque(nums, sortedNums, counts, mid + 1, end);
        
        // since nums[start, mid] and nums[mid + 1, end] are sorted
        // for each num in [start, mid], we know how many num in [mid + 1, end] less than it
        for (int i = start; i <= mid; i++) {
            auto pos = lower_bound(sortedNums.begin() + mid + 1, 
                                   sortedNums.begin() + end + 1, nums[i]);            
            counts[i] += pos - (sortedNums.begin() + mid + 1);
        }
        
        // here use sort(), but implemented as mergesort can be more faster        
        sort(sortedNums.begin() + start, sortedNums.begin() + end + 1);  
    }
};































































