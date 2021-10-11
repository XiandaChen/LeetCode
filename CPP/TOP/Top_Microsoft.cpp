// 1448. Count Good Nodes in Binary Tree
// Input: root = [3,1,4,3,null,1,5]; Output: 4 (3,3,4,5)
class Solution {
public:
    int goodNodes(TreeNode* root) {
        return dfs(root, INT_MIN);
    }
    int dfs(TreeNode* root, int curMax) {
        if (!root) return 0;
        int cnt = 0;
        if (root->val >= curMax) {
            cnt++;
            curMax = root->val;
        }
        return cnt + dfs(root->left, curMax) + dfs(root->right, curMax);
    }
};

// 588. Design In-Memory File System
class FileSystem {
public:
    FileSystem() {
        dirs["/"];
    }
    
    vector<string> ls(string path) {
        if (files.count(path)) { // filepath
            int idx = path.find_last_of('/');
            return {path.substr(idx + 1)};
        }
        
        // dirpath
        auto t = dirs[path];
        return vector<string> (t.begin(), t.end());
    }
    
    void mkdir(string path) {
        istringstream is(path);
        string t = "", dir = "";
        while (getline(is, t, '/')) {
            if (t.empty()) continue;
            if (dir.empty()) dir += "/";
            dirs[dir].insert(t);
            if (dir.size() > 1) dir += "/";
            dir += t;
        }
    }
    
    void addContentToFile(string filePath, string content) {
        int idx = filePath.find_last_of('/');
        string dir = filePath.substr(0, idx);
        string file = filePath.substr(idx + 1);
        if (dir.empty()) dir = "/";
        if (!dirs.count(dir)) mkdir(dir);
        dirs[dir].insert(file);
        files[filePath].append(content);
    }
    
    string readContentFromFile(string filePath) {
        return files[filePath];
    }
private:
    unordered_map<string, string> files; // filename-content
    unordered_map<string, set<string>> dirs; // dir-<files, subdir>
};

// 37. Sudoku Solver
class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
    bool helper(vector<vector<char>> & board, int i, int j) {
        if (i == 9) return true; // successfully check all rows
        if (j >= 9) return helper(board, i + 1, 0); // check new row
        if (board[i][j] != '.') return helper(board, i, j + 1); // not need to feel position[i][j]
        
        for (char c = '1'; c <= '9'; c++) {
            if (!isValid(board, i, j, c)) continue; // char c not fit
            board[i][j] = c;
            
            if (helper(board, i, j + 1)) return true; // 
            board[i][j] = '.'; // else, reset pos[i][j] to '.'
        }
        
        return false;
    }
    bool isValid(vector<vector<char>> & board, int i, int j, char val) {
        for (int x = 0; x < 9; x++) {
            if (board[x][j] == val) return false;
        }
        for (int y = 0; y < 9; y++) {
            if (board[i][y] == val) return false;
        }
        
        // 9 3x3 subboxes have exactly 1-9 once
        int row = i - i % 3, col = j - j % 3;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (board[row + x][col + y] == val) return false;
            }
        }
        
        return true;
    }
};

// 79. Word Search
// Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], 
// word = "ABCCED"; Output: true
class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty() || board[0].empty()) return false;
        int m = (int)board.size(), n = (int)board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (search(board, word, 0, i, j, visited)) return true;
            }
        }
        return false;
    }
    bool search(vector<vector<char>>& board, string word, int idx, int i, int j, vector<vector<bool>> & visited) {
        if (idx == word.size()) return true;
        int m = (int)board.size(), n = (int)board[0].size();
        if (i < 0 || j < 0 || i >= m || j >= n
           || visited[i][j] || board[i][j] != word[idx]) return false;
        visited[i][j] = true;
        bool res = search(board, word, idx + 1, i - 1, j, visited)
                    || search(board, word, idx + 1, i + 1, j, visited)
                    || search(board, word, idx + 1, i, j - 1, visited)
                    || search(board, word, idx + 1, i, j + 1, visited);
        visited[i][j] = false; // reset, backtrace
        return res;
    }
};
// 212. Word Search II, return all words on the board.
// Input: board = [["o","a","a","n"],["e","t","a","e"],["i","h","k","r"],["i","f","l","v"]], 
// words = ["oath","pea","eat","rain"]; Output: ["eat","oath"]
class Solution {
public:
    struct TrieNode {
        TrieNode * child[26];
        string str;
        TrieNode() : str("") {
            for (auto & a : child) a = nullptr;
        }
    };
    struct Trie {
        TrieNode * root;
        Trie(): root(new TrieNode()) {};
        
        void insert(string word) {
            TrieNode * p = root;
            for (char & c: word) {
                int idx = c - 'a';
                if (!p->child[idx]) p->child[idx] = new TrieNode();
                p = p->child[idx];
            }
            p->str = word;
        }
    };
    
    vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
        if (board.empty() || words.empty()) return {};
            
        // construct Trie to encode the words
        Trie T;
        for (string & s: words) T.insert(s);
        
        // search words in the board
        int m = board.size(), n = board[0].size();
        vector<string> res;
        
        vector<vector<bool>> visited(m, vector<bool>(n));
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // search from each [i][j] position
                if (T.root->child[board[i][j] - 'a'])
                    search(board, T.root->child[board[i][j] - 'a'], i, j, visited, res);
            }
        }
        
        return res;
    }
    
    void search(vector<vector<char>> & board, TrieNode * p, int i, int j, 
                vector<vector<bool>> & visited, vector<string> & res) {        
        if (!p->str.empty()) { // word exists
            res.push_back(p->str); 
            p->str.clear();  // avoid duplicates in res
        }

        visited[i][j] = true;
        
        int m = (int)board.size(), n = (int)board[0].size();
        int dim[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        // search up, down, left, right direction from [i][j]
        for (auto & a: dim) {
            int x = a[0] + i, y = a[1] + j;
            if (0 <= x && x < m && 0 <= y && y < n
               && !visited[x][y] && p->child[board[x][y] - 'a']) {
                search(board, p->child[board[x][y] - 'a'], x, y, visited, res);
            }
        }
                
        visited[i][j] = false; // reset, backtrace
    }
};  


// 208. Implement Trie (Prefix Tree)
class Trie {
public:
    struct TrieNode{
        TrieNode * child[26];
        bool isWord;
        TrieNode(): isWord(false) {
            for (auto & a : child) a = nullptr;
        }
    };
    
    Trie() {
        root = new TrieNode();
    }
    
    void insert(string word) {
        TrieNode * p = root;
        for (char & c : word) {
            int idx = c - 'a';
            if (!p->child[idx]) p->child[idx] = new TrieNode();
            p = p->child[idx];
        }
        p->isWord = true;
    }
    
    bool search(string word) {
        TrieNode * p = root;
        for (char & c : word) {
            int idx = c - 'a';
            if (!p->child[idx]) return false;
            p = p->child[idx];
        }
        return p->isWord;
    }
    
    bool startsWith(string prefix) {
        TrieNode * p = root;
        for (char & c : prefix) {
            int idx = c - 'a';
            if (!p->child[idx]) return false;
            p = p->child[idx];
        }
        return true;
    }
private:
    TrieNode * root;
};



// 443. String Compression
class Solution {
public:
    int compress(vector<char>& chars) {
        int n = chars.size(), cur = 0;
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && chars[j] == chars[i]) j++;
            
            chars[cur++] = chars[i]; // write in-place
            
            // only one char, not need to add cnt
            if (j - i == 1) continue; 
            
            // for repeating char, add cnt
            for (char c : to_string(j - i)) chars[cur++] = c;
        }
        return cur;
    }
};


// 151. Reverse Words in a String
// Input: s = "  hello world  "; Output: "world hello"
class Solution {
public:
    string reverseWords(string s) {
        istringstream is(s);
        s = "";
        string tmp = "";
        while (getline(is, tmp, ' ')) {
            if (tmp.empty()) continue; // getline get one space each time
            s = (s.empty()) ? tmp : (tmp + " " + s);
        }
        return s;
    }
};
class Solution {
public:
    string reverseWords(string s) {
        int n = s.size(), idx = 0;
        reverse(s.begin(), s.end());
        
        for (int i = 0; i < n; i++) {
            if (s[i] != ' ') {
                if (idx != 0) s[idx++] = ' '; // add ' ' before new word
            
                int j = i; 
                while (j < n && s[j] != ' ') s[idx++] = s[j++];

                // reverse the word
                reverse(s.begin() + idx - (j - i), s.begin() + idx);

                i = j; // for next word
            }
        }
        s.resize(idx);
        return s;
    }
};

// 186. Reverse Words in a String II
// Given a character array s, reverse the order of the words.
// Input: s = ["t","h","e"," ","s","k","y"," ","i","s"," ","b","l","u","e"]
// Output: ["b","l","u","e"," ","i","s"," ","s","k","y"," ","t","h","e"]
class Solution {
public:
    void reverseWords(vector<char>& s) {
        int n = s.size();
        
        reverse(s.begin(), s.end()); // reverse the whole string
        
        for (int i = 0, j = 0; i < n; i = j + 1) {
            for (j = i; j <= n; j++) {
                if (j == n || s[j] == ' ') {
                    reverse(s.begin() + i, s.begin() + j);  // reverse each word
                    break;
                }            
            }
        }
    }
};

// 1647. Minimum Deletions to Make Character Frequencies Unique
class Solution {
public:
    int minDeletions(string s) {
        unordered_map<char, int> m; // char-freq
        vector<int> freq;  
        set<int> fset; // freq set after deletion
        int res = 0;
        
        for (char c : s) m[c]++;
        
        for (auto a : m) freq.push_back(a.second);
        sort(freq.begin(), freq.end()); // sort frequency
        
        for (int i = freq.size() - 1; i >= 0; i--) { // search from largest freq
            if (!fset.count(freq[i])) {
                fset.insert(freq[i]);
            }
            else { // freq[i] already exists, then deletion
                int k = freq[i] - 1;
                while (k > 0 && fset.count(k)) k--;
                
                if (k > 0) fset.insert(k);
                
                res += freq[i] - k; // add deletions
            }
        }
        
        return res;
    }
};

// int-
// 0-A, 1-B, ..., 27-BB, ..., 79-BBBB
string get_col_num(int col) {
    if (col < 0 ) return "";

    int quot = 0, remain = 0;
    string res = "";

    quot = col / 26;
    remain = col % 26;

    // 27 => BB
    for (int i = 0; i < (quot + 1); i++) {
        res += 'A' + remain;
    }

    return res;
}
// 0-A, 1-B, ..., 27-AB, ..., 79-CB, ..., 731-ABD
string get_col_num_2(int col) {
    if (col < 0 ) return "";

    int quot = 0, remain = 0;
    string res = "";

    // 27 => AB 
    quot = col / 26;
    remain = col % 26;  // NOTE, not quot
    res += 'A' + remain;

    while (0 < quot) {
        int tmp = quot;
        quot = tmp / 26;
        remain = tmp % 26;
        
        res += 'A' + (remain - 1);
    }
    
    reverse(res.begin(), res.end());
    
    return res;
}

// 146. LRU Cache,  Least Recently Used (LRU) cache.
// The functions get and put must each run in O(1) average time complexity.
class LRUCache {
public:
    LRUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if (!iter.count(key)) return -1;
        
        int val = iter[key]->second;
        
        // move this key-val to cache front
        // void splice (iterator position, list& x, iterator i);
        cache.splice(cache.begin(), cache, iter[key]);  // NOTE, time O(1)
        
        // cache.erase(m[key]);  // NOTE, time O(n)
        // cache.push_front({key, val});  // time O(1)
        
        return val;
    }
    
    void put(int key, int value) {
        if (iter.count(key)) {
            cache.erase(iter[key]);
        }
        
        cache.push_front({key, value});
        
        iter[key] = cache.begin();
        
        if (cache.size() > cap) { // NOTE: cache.size(), not m.size()
            int k = cache.rbegin()->first;  // NOTE, rbegin, not end()
            iter.erase(k);
            
            cache.pop_back();
        }
    }
private:
    int cap;
    list<std::pair<int, int>> cache; //cache: key-val
    unordered_map<int, list<std::pair<int, int>>::iterator> iter; // key-iterator in cache
};

// 460. LFU Cache,  Least Frequently Used (LFU) 
// The functions get and put must each run in O(1) average time complexity.
// When there is a tie (i.e., two or more keys with the same frequency), 
// the least recently used key would be invalidated.
class LFUCache {
public:
    LFUCache(int capacity) {
        cap = capacity;
    }
    
    int get(int key) {
        if (!cache.count(key)) return -1;
        
        freq[cache[key].second].erase(iter[key]);  // remove key from old freq list
        
        cache[key].second += 1; // increment freq for key
        freq[cache[key].second].push_front(key);  // add key to new freq list
        
        iter[key] = freq[cache[key].second].begin();  // key inserted at the front of freq list
        
        if (freq[minFreq].size() == 0) minFreq++;
        
        return cache[key].first;
    }
    
    void put(int key, int value) {
        if (cap <= 0) return;
        
        // if key in cache
        if (get(key) != -1) { // update its freq and iter in get(key) func
            cache[key].first = value; // update its value in cache 
            return ;
        }
        
        // else if key not in cache
        
        if (cap <= cache.size()) { // remove LFU one
            auto lfu = freq[minFreq].back(); 
            cache.erase(lfu);  
            freq[minFreq].pop_back();
            iter.erase(lfu);
        }
        
        cache[key] = {value, 1}; // add new key-val
        freq[1].push_front(key);
        iter[key] = freq[1].begin();
        minFreq =  1;
    }
private:
    int cap, minFreq;
    unordered_map<int, pair<int, int>> cache; // cache: key-<value, freq>
    unordered_map<int, list<int>> freq; // freq-keys that have same key
    unordered_map<int, list<int>::iterator> iter; // key-iterator in freq list
};

// 642. Design Search Autocomplete System
// For each input character except '#', return the top 3 historical hot sentences 
// that have the same prefix as the part of the sentence already typed.
class AutocompleteSystem {
public:
    AutocompleteSystem(vector<string>& sentences, vector<int>& times) {
        for (int i = sentences.size() - 1; i >= 0; i--) {
            freq[sentences[i]] = times[i];
        }
        data = "";
    }
    
    vector<string> input(char c) {
        // the user finished the input
        if (c ==  '#') {
            freq[data]++; // NOTE, not freq[data] = 1
            data = "";
            return {};
        }
        
        // update the prefix with input c
        data += c;
        
        // construct minHeap to hold top-3 hot sentences with prefic data
        // when minHeap.size > 3, evict the top elem that has min freq
        auto cmp = [] (pair<string, int> & a, pair<string, int> & b) {
            return a.second > b.second 
                || (a.second == b.second && a.first < b.first); // same hot degree, maintain ASCII smaller one
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> q(cmp);
        
        for (auto & f : freq) {
            int len1 = data.size(), len2 = f.first.size();
            if (len1 > len2) continue; // input data is longer than the sentence
            
            bool isPrefix = true;
            for (int i = 0; i < len1; i++) {
                if (data[i] != f.first[i]) { // data is not prefix in the sentence
                    isPrefix = false;
                    break; 
                }
            }
            
            if (isPrefix) {
                q.push(f);
                
                if (q.size() > 3) {
                    q.pop();
                }
            }
        }
        
        // results
        vector<string> res(q.size());
        for (int i = q.size() - 1; i >= 0; i--) { // reversed order, since minHeap
            auto t = q.top(); q.pop();
            res[i] = t.first;
        }
        
        return res;
    }
private:
    unordered_map<string, int> freq; // sentence-time
    string data; // to hold input data
};

// 706. Design HashMap
// Time: O(1), Space: O(K), K most pairs
class MyHashMap {
public:
    MyHashMap() {
        data.resize(1e6 + 1, -1);     }
    void put(int key, int value) {
        data[key] = value;    }
    int get(int key) {
        return data[key];    }
    void remove(int key) {
        data[key] = -1;    }
private:
    vector<int> data;
};
// To optimize space usage
class MyHashMap {
public:
    MyHashMap() {
        data.resize(1001, vector<int>());
    }
    void put(int key, int value) {
        int hashKey = key % 1000;
        if (data[hashKey].empty()) {
            data[hashKey].resize(1001, -1);
        }
        data[hashKey][key / 1000] = value;
    }
    int get(int key) {
        int hashKey = key % 1000;
        if (!data[hashKey].empty()) {
            return data[hashKey][key / 1000];
        }
        return -1;
    }
    void remove(int key) {
        int hashKey = key % 1000;
        if (!data[hashKey].empty()) {
            data[hashKey][key / 1000] = -1;
        }
    }
private:
    vector<vector<int>> data;
};


// 934. Shortest Bridge between two islands
class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size(), startX = -1, startY = -1, res = 0;
        queue<int> q; // hold 1s, search layer by layer
        
        // find the first non-0 x and y to start the search
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) continue;
                // if (grid[i][j] == 1) {
                    startX = i;
                    startY = j;
                    break;
                // }
            }
            if (startX != -1) break;
        }
        
        // 1. find the first island, all 1's for that island
        helper(grid, startX, startY, q);
        
        // 2. BFS, layer-by-layer to search the island
        int dim[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        while (!q.empty()) {
            for (int i = q.size(); i > 0; i--) {
                int t = q.front(); q.pop();

                for (auto & a : dim) { // search four directions
                    int x = t / n + a[0], y = t % n + a[1];
                    
                    if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] == 2) continue;
                    
                    if (grid[x][y] == 1) return res; // two islands are connected
                    
                    grid[x][y] = 2;
                    q.push(x * n + y);
                }
            }
            res++;
        }
        
        return res;
    }
    
    void helper(vector<vector<int>> & grid, int x, int y, queue<int> & q) {
        int n = grid.size();
        
        // grid[x][y] == 2: node has been visited
        if (x < 0 || x >= n || y < 0 || y >= n 
            || grid[x][y] == 0 || grid[x][y] == 2) return;
        
        q.push(x * n + y);  // convert 2D idx to 1D idx
        
        grid[x][y] = 2;  // set visited
        
        // traverse four directions
        int dim[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto & a : dim) {
            helper(grid, x + a[0], y + a[1], q);
        }
    }
};

// 297. Serialize and Deserialize Binary Tree
class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        if (!root) return "";
        
        // level-order traversal
        queue<TreeNode*> q {{root}};
        string res = "";  // NOTE: must use to_val(t->val)
        // ostringstream os;
        
        while (!q.empty()) {
            for (int i = q.size(); i > 0; i--) {
                auto t = q.front(); q.pop();
                
                if (t) {
                    res += to_string(t->val) + " "; // NOTE: must to_string
                    // os << t->val << " ";
                    q.push(t->left);
                    q.push(t->right);
                }
                else {
                    res += "# ";
                    // os << "# ";
                }
            }
        }
        
        return res;
        // return os.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        if (data.empty()) return nullptr;
        
        istringstream is(data); 
        string val;
        
        is >> val;
        TreeNode * res = new TreeNode(stoi(val)), * root = res;
        
        queue<TreeNode*> q{{root}};
        
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            
            // left node
            is >> val;
            if (val != "#") {
                TreeNode * node = new TreeNode(stoi(val));
                t->left = node;
                q.push(node); // add
            }
            
            // right node
            is >> val;
            if (val != "#") {
                TreeNode * node = new TreeNode(stoi(val));
                t->right = node;
                q.push(node); // add
            }
        }
        
        return res;
    }
};

// 428. Serialize and Deserialize N-ary Tree
class Codec {
public:
    // Encodes a tree to a single string.
    string serialize(Node* root) {
        if (!root) return "#";  // NOTE, "#"
        
        queue<Node*> q {{root}};
        string res = "";
        
        while (!q.empty()) {
            auto t = q.front(); q.pop();
            
            // NOTE, children size to seperate nodes
            res += to_string(t->val) + " " + to_string(t->children.size()) + " ";
            
            for (auto & a : t->children) {
                q.push(a);
            }
        }
        
        return res;
    }
	
    // Decodes your encoded data to tree.
    Node* deserialize(string data) {
        if (data.empty()) return nullptr;  
        
        istringstream is(data);
        string val, size;
        
        is >> val;
        if (val == "#") return nullptr;

        is >> size;
        Node * res = new Node(stoi(val), {}), * root = res;
        
        queue<Node*> qNode{{root}};
        queue<int> qSize{{stoi(size)}};
        
        while (!qNode.empty()) {
            auto t = qNode.front(); qNode.pop();
            int len = qSize.front(); qSize.pop();
            
            for (int i = 0; i < len; i++) {
                if (!(is >> val)) break;
                if (!(is >> size)) break;
                
                Node * node = new Node(stoi(val), {});
                qNode.push(node);
                
                qSize.push(stoi(size));
                
                // NOTE: add child nodes
                t->children.push_back(node);
            }
            
        }
        
        return res;
    }
};

// 348. Design Tic-Tac-Toe, O(N^2)
class TicTacToe {
public:
    TicTacToe(int n) {
        board.resize(n, vector<int>(n, 0));
    }
    
    int move(int row, int col, int player) {
        // 0: empty, 1: player1, 2: player2
        board[row][col] = player;
        
        int n = board.size(), i = 0, j = 0;
        
        // check horizontal
        for (j = 1; j < n; j++) {
            if (board[row][j] != board[row][j - 1]) break;
        }
        if (j == n) return player;
        
        // check vertical
        for (i = 1; i < n; i++) {
            if (board[i][col] != board[i - 1][col]) break;
        }
        if (i == n) return player;
        
        // check diagonal
        if (row == col) { // left diagonal
            for (i = 1; i < n; i++) {
                if (board[i][i] != board[i - 1][i - 1]) break;
            }
            if (i == n) return player;
        }
        // NOTE, not "else if" for case row=col=n/2
        if (row + col == n - 1) { // right diagonal
            for (i = 1; i < n; i++) {
                if (board[n - 1 - i][i] != board[n - i][i - 1]) break;
            }
            if (i == n) return player;
        }
        
        return 0;
    }
private:
    vector<vector<int>> board;
};
class TicTacToe {
public:
    TicTacToe(int n) {
        rows.resize(n);
        cols.resize(n);
        diag = 0;
        rev_diag = 0;
        N = n;
    }
    
    int move(int row, int col, int player) {
        int add = (player == 1) ? 1 : -1;
        
        rows[row] += add;
        cols[col] += add;
        
        diag += (row == col) ? add : 0;  // NOTE, add, not 1
        rev_diag += (row + col == N - 1) ? add: 0;
        
        return (abs(rows[row]) == N || abs(cols[col]) == N
               || abs(diag) == N || abs(rev_diag) == N) ? player : 0;
    }
private:
    // num moves that player1 placed on each row
    // increment 1 if player1 moves on the row
    // derease 1 if player1 moves on that row
    vector<int> rows, cols; 
    
    // num moves that player1 placed on diagonal and reverse diagonal
    int diag, rev_diag, N;
};


// 1578. Minimum Deletion Cost to Avoid Continuouse Repeating Letters
// Input: s = "abaac", cost = [1,2,3,4,5]; Output: 3
// Explanation: Delete the letter "a" with cost 3 to get "abac" (String without two identical letters next to each other).
class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int n = s.size(), res = 0;
        int sumCost = 0, maxCost = 0; // sum cost (max cost) for repeating letters
        
        for (int i = 0; i < n; i++) {
            if (i == 0 || s[i] != s[i - 1]) {
                // delete all repeating letters except the one with maxCost
                res += (sumCost - maxCost); 
                sumCost = maxCost = cost[i]; // for new char
            }
            else {
                sumCost += cost[i];
                maxCost = max(maxCost, cost[i]);
            }
        }
        
        res += sumCost - maxCost; // NOTE, for last repeating letters, "aabaa"
        
        return res;
    }
};

// 540. Single Element in a Sorted Array
// Input:   arr[] = {1, 1, 3, 3, 4, 5, 5, 7, 7, 8, 8}; Output:  4
// All elements before the required have first occurrence at even index (0, 2, ..) 
// and next occurrence at odd index (1, 3, …). [even, odd]
// And all elements after the required element have first occurrence at odd index 
// and next occurrence at even index. [odd, even]
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size(), left = 0, right = n - 1;
        
        while (left < right) {
            int mid = left + (right - left) / 2;
            
            // before the single elem,  
            // for each pair, the first elem is at even idx
            if (mid % 2 == 0) {
                if (mid + 1 < n && nums[mid] == nums[mid + 1])
                    left = mid + 2; // NOTE, + 2
                else 
                    right = mid;  // NOTE, not -2
            }
            else {
                if (mid - 1 >= 0 && nums[mid - 1] == nums[mid])
                    left = mid + 1;
                else
                    right = mid;  // NOTE, not -1
            }
        }
        
        return nums[right];
    }
};

// 277. Find the Celebrity
/* The knows API is defined for you.
      bool knows(int a, int b); */
class Solution {
public:
    int findCelebrity(int n) {
        for (int i = 0; i < n; i++) { // check if i is celebrity
            int j = 0;
            
            // i is celebrity if only if i knows no one and all other j knows i
            for (; j < n; j++) { 
                if (i != j && (knows(i, j) || !knows(j, i))) break; // i is not celebrity
            }
            
            if (j == n) return i;
        }
        
        return -1;
    }
};

// 1344. Smaller Angle Between Hands of a Clock
class Solution {
public:
    double angleClock(int hour, int minutes) {
        // hour hand, referred to 00
        double h = (hour % 12) + minutes / 60.0; // NOTE, 60.0
        double hangle = 360.0 / 12 * h;
        
        double mangle = 360.0 / 60 * minutes;
                
        double angle = abs(mangle - hangle);
        
        return (angle <= 180) ? angle : (360 - angle);
    }
};

// 1405. Longest Happy String
// A string is called happy if it does not have any of the strings 'aaa', 'bbb' or 'ccc' as a substring.
// Input: a = 1, b = 1, c = 7; Output: "ccaccbcc"
class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        auto cmp = [](pair<int, char> & a, pair<int, char> & b) { // maxHeap
            return a.first < b.first || (a.first == b.first && a.second > b.second);
        };
        priority_queue<pair<int, char>, vector<pair<int, char>>, decltype(cmp)> q(cmp);
        
        if (a > 0) q.push({a, 'a'});
        if (b > 0) q.push({b, 'b'});
        if (c > 0) q.push({c, 'c'});
            
        string res = "";
        
        // place the maximum value character 2 times and then its next smaller 1 time.
        while (!q.empty()) {
            auto cur = q.top(); q.pop();
            
            // add 2 characters as per round if possible
            for (int i = min(cur.first, 2); i > 0; i--) {
                res += cur.second;
                cur.first--;                
            }
            
            if (q.empty()) break;
            
            auto next = q.top(); q.pop();
            
            // if next char is the maxmium, i.e., next.first > cur.first
            // add two next.second if possible
            if (next.first >= cur.first) {
                res += next.second;
                next.first--;
            }
            if (next.first > 0) { // add the second next.second if possible
                res += next.second;
                next.first--;
            }
            
            if (cur.first) q.push(cur);
            if (next.first) q.push(next);
        }
        
        return res ; 
    }
};

// 489. Robot Room Cleaner
class Solution {
public:
    vector<vector<int>> dirs = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}}; // up, right, down, left
    void cleanRoom(Robot& robot) {
        unordered_set<string> visited;
        helper(robot, 0, 0, 0, visited); // assume robot initial location as (0,0) and face up
    }
    void helper(Robot & robot, int x, int y, int dir, unordered_set<string> & visited) {
        robot.clean();
        visited.insert(to_string(x) + "_" + to_string(y));
        
        for (int i = 0; i < 4; i++) { // search up, right, down, left
            int cur = (i + dir) % 4, newX = x + dirs[cur][0], newY = y + dirs[cur][1];
            
            // if <newX, newY> is not visited, and reachable
            if (!visited.count(to_string(newX) + "_" + to_string(newY)) && robot.move()) {
                // move forward
                helper(robot, newX, newY, cur, visited); 
                
                // return backward
                robot.turnRight();
                robot.turnRight();
                robot.move();  // return to previous locatioin
                robot.turnRight();
                robot.turnRight(); // turn 180degree to previous direction
            }
            
            // move forward (UP) ->  turnRight -> move forward (RIGHT) 
            //     -> turnRight -> move forward (DOWN) -> turnRight -> move forward (LEFT)
            robot.turnRight();
        }
    }
};

// 384. Shuffle an Array
class Solution {
public:
    Solution(vector<int>& nums) {
        original = nums;
    }
    
    vector<int> reset() {
        return original;
    }
    
    vector<int> shuffle() {
        vector<int> res = original;
        int n = res.size();
        for (int i = 0; i < n; i++) {
            // int idx = rand() % n;
            int idx = i + rand() % (n - i);
            swap(res[i], res[idx]);
        }
        return res;
    }
private:
    vector<int> original;
};

// 722. Remove Comments
class Solution {
public:
    vector<string> removeComments(vector<string>& source) {
        vector<string> res;
        string out = "";
        bool blocked = false;
        
        for (auto & line : source) {
            int len = line.size();
            for (int i = 0; i < len; i++) {
                if (!blocked) { // if not commented yet
                    if (i == len - 1) out += line[i];
                    else {
                        string t = line.substr(i, 2);
                        if (t == "//") {
                            break; // the rest of the characters to the right is ignored
                        }
                        else if (t == "/*") {
                            blocked =  true;
                            ++i;  
                        }
                        else {
                            out += line[i];
                        }
                    }
                }
                else { // if blocked, find the end of block comment
                    if (i < len - 1) {
                        if (line.substr(i, 2) == "*/") {
                            blocked = false;
                            ++i;
                        }
                    }
                }
                
            }
            
            // add valid code in this line to result
            if (!blocked && !out.empty()) {
                res.push_back(out);
                out = "";
            }
        }
        
        return res;
    }
};

// 1304. Find N Unique Integers Sum up to Zero
class Solution {
public:
    vector<int> sumZero(int n) {
        vector<int> res;
        
        if (n & 1) { // odd number
            res.push_back(0);
            n--;
        }
        
        int x = 1;
        while (n > 0) { // even number, add (x,-x) each time
            res.push_back(x);
            res.push_back(-x);
            
            n -= 2;
            x++;
        }
        
        return res;
    }
};

// 1615. Maximal Network Rank
// The network rank of two different cities is defined as the total number of directly connected roads to either city. 
// If a road is directly connected to both cities, it is only counted once.
class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        unordered_map<int, set<int>> graph; // node-connectedNodes
        
        int res = 0;
        
        for (auto & road : roads) {
            graph[road[0]].insert(road[1]);
            graph[road[1]].insert(road[0]);            
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!graph[i].count(j)) { // i, j are seperate
                    res = max(res, int(graph[i].size() + graph[j].size()));
                }
                else { // nodes i and j are connected
                    res = max(res, int(graph[i].size() + graph[j].size() - 1));
                }
            }
        }
        
        return res;
    }
};

// 769. Max Chunks To Make Sorted
// array: a permutation of the integers in the range [0, n - 1]
// Input: arr = [1,0,2,3,4]; Output: 4
// Explanation: [1, 0], [2], [3], [4] is the highest number of chunks possible.
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size(), res = 0;
        
        for (int i = 0; i < n; i++) {
            int curMax = arr[i], j = i + 1;
            for (; j <= curMax; j++) {
                curMax = max(curMax, arr[j]); // update the farest reachable pos
                if (curMax >= arr.back()) return res + 1; 
            }
            
            i = j - 1; // NOTE - 1
            res++;
        }
        
        return res;
    }
};
// 768. Max Chunks To Make Sorted II
// arr: num can be larger than N, and may have duplicates
class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size(), res = 0;
        long sum1 = 0, sum2 = 0; // NOTE, long
        
        vector<int> expect = arr;
        sort(expect.begin(), expect.end());
        
        for (int i = 0; i < n; i++) {
            sum1 += arr[i];
            sum2 += expect[i];
            if (sum1 == sum2) res++;
        }
        
        return res;
    }
};

// 915. Partition Array into Disjoint Intervals
class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size(), maxLeft = INT_MIN;
        vector<int> minRight(n);
        
        minRight[n - 1] = nums[n - 1];
        for (int i = n - 2; i >= 0; i--) {
            minRight[i] = min(nums[i], minRight[i + 1]);
        }
        
        for (int i = 0; i < n - 1; i++) { // NOTE, n-1, i.e., left and right are non-empty
            maxLeft = max(maxLeft, nums[i]);
            if (maxLeft <= minRight[i + 1]) return i + 1;
        }
        
        return 0;
    }
};
// Space O(1)
class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size(), partitionIdx = 0, prevMax = nums[0], curMax = nums[0];
        
        for (int i = 1; i < n; i++) {
            curMax = max(curMax, nums[i]);
            if (nums[i] < prevMax) { // Every element in left must <= in right.
                partitionIdx = i;
                prevMax = curMax;
            }
        }
        
        return partitionIdx + 1;
    }
};

// 545. Boundary of Binary Tree
class Solution {
public:
    vector<int> boundaryOfBinaryTree(TreeNode* root) {
        if (!root) return {};
        
        vector<int> res;
        
        if (root->left || root->right) res.push_back(root->val); // add root val
        
        // If the root does not have a left child, then the left boundary is empty.
        leftBoundary(root->left, res);
        leaves(root, res);
        rightBoundary(root->right, res);
        
        return res;
    }
    
    void leftBoundary(TreeNode * root, vector<int> & res) {
        if (!root || (!root->left && !root->right)) return; // empty root, or root is a leaf
        res.push_back(root->val);
        if (root->left) leftBoundary(root->left, res);
        else leftBoundary(root->right, res);
    }
    
    void rightBoundary(TreeNode * root, vector<int> & res) {
        if (!root || (!root->left && !root->right)) return; // empty root, or root is a leaf
        if (root->right) rightBoundary(root->right, res);
        else rightBoundary(root->left, res);
        res.push_back(root->val);  // NOTE, ordering
    } 
    
    void leaves(TreeNode * root, vector<int> & res) {
        if (!root) return;
        if (!root->left && !root->right) res.push_back(root->val);
        if (root->left) leaves(root->left, res);
        if (root->right) leaves(root->right, res);
    }
};



























































