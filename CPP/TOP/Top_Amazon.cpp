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






























































