// 155. Min Stack
class MinStack {
public:
    /** initialize your data structure here. */
    MinStack() {
        minval = INT_MAX;
    }    
    void push(int x) {
        if (x <= minval) {
            st.push(minval); // push pre_minval
            minval = x; // update minval
        }
        st.push(x);
    }    
    void pop() {
        int t = st.top(); st.pop();
        if (t == minval) {
            minval = st.top(); // update minval = pre_minval
            st.pop(); // pop pre_minval that duplicated in stack
        }
    }
    int top() {
        return st.top();
    }    
    int getMin() {
        return minval;
    }
private:
    int minval;
    stack<int> st;
};
 
//173. Binary Search Tree Iterator 
// Binary Tree Inorder Traversal, using stack
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        while (root) {
            st.push(root);
            root = root->left;
        }
    }   
    /** @return the next smallest number */
    int next() {
        TreeNode * p = st.top(); st.pop();
        int res = p->val;
        if (p->right) {
            p = p->right;
            while (p) {
                st.push(p);
                p = p->left;
            }
        }
        return res;
    }   
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !st.empty();
    }
private:
    stack<TreeNode*> st;
};

// 208. Implement Trie (Prefix Tree)
// Implement a trie with insert, search, and startsWith methods
class Trie {
public:
    struct TrieNode {
    public:
        TrieNode * child[26];
        bool isWord;
        TrieNode (): isWord(false) {
            for (auto & a : child) a = nullptr;
        }
    };
    /** Initialize your data structure here. */
    Trie() { root = new TrieNode();}
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode * p = root;
        for (auto & ch : word) {
            int i = ch - 'a';
            if (!p->child[i]) p->child[i] = new TrieNode();
            p = p->child[i];
        }
        p->isWord = true;
    }    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode * p = root;
        for (auto & ch : word) {
            int i = ch - 'a';
            if (!p->child[i]) return false;
            p = p->child[i];
        }
        return p->isWord;
    }   
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode * p = root;
        for (auto & ch : prefix) {
            int i = ch - 'a';
            if (!p->child[i]) return false;
            p = p->child[i];
        }
        return true;
    }
private:
    TrieNode * root;
};

// 211. Add and Search Word - Data structure design
// A word could contain the dot character '.' to represent any one letter
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
    /** Returns if the word is in the data structure. 
	A word could contain the dot character '.' to represent any one letter. */
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

// 1268. Search Suggestions System
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

// 588. Design In-Memory File System
class FileSystem {
public:
    FileSystem() {
        dirs["/"];    }
    vector<string> ls(string path) {
        if (files.count(path)) { // filepath
            int idx = path.find_last_of('/');
            return {path.substr(idx + 1)};        }
        // dirpath
        auto t = dirs[path];
        return vector<string> (t.begin(), t.end());    }
    void mkdir(string path) {
        istringstream is(path);
        string t = "", dir = "";
        while (getline(is, t, '/')) {
            if (t.empty()) continue;
            if (dir.empty()) dir += "/";
            dirs[dir].insert(t);
            if (dir.size() > 1) dir += "/";
            dir += t;        }    }
    void addContentToFile(string filePath, string content) {
        int idx = filePath.find_last_of('/');
        string dir = filePath.substr(0, idx);
        string file = filePath.substr(idx + 1);
        if (dir.empty()) dir = "/";
        if (!dirs.count(dir)) mkdir(dir);
        dirs[dir].insert(file);
        files[filePath].append(content);    }
    
    string readContentFromFile(string filePath) {
        return files[filePath];    }
private:
    unordered_map<string, string> files; // filepath-content
    unordered_map<string, set<string>> dirs; // dir-<files, subdir>
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

// 622. Design circular queue
class circularQueue {	
	typedef struct {
		int *data;
		int head, tail, cnt, size;
	} MyCircularQueue;

	bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
	  return obj->cnt == 0;
	}

	bool myCircularQueueIsFull(MyCircularQueue* obj) {
	  return obj->cnt == obj->size;
	}

	void myCircularQueueFree(MyCircularQueue* obj) {
		free(obj);
	}

	MyCircularQueue* myCircularQueueCreate(int k) {
		MyCircularQueue* q = malloc(sizeof(MyCircularQueue));
		q->data = malloc(k * sizeof(int));
		q->head = q->tail = q->cnt = 0;
		q->size = k;
		return q;
	}

	bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
		if (myCircularQueueIsFull(obj)) return false;
		obj->data[obj->tail] = value;
		obj->tail = (obj->tail + 1) % obj->size;    // NOTE
		obj->cnt++;
		return true;
	}

	bool myCircularQueueDeQueue(MyCircularQueue* obj) {
		if (myCircularQueueIsEmpty(obj)) return false;
		obj->head = (obj->head + 1) % obj->size;
		obj->cnt--;
		return true;
	}

	int myCircularQueueFront(MyCircularQueue* obj) {
		if (myCircularQueueIsEmpty(obj)) return -1;
		return obj->data[obj->head];
	}

	int myCircularQueueRear(MyCircularQueue* obj) {
		if (myCircularQueueIsEmpty(obj)) return -1;
		return obj->data[(obj->tail - 1 + obj->size) % obj->size];  // NOTE
	}
};
class MyCircularQueue {
public:
    /** Initialize your data structure here. Set the size of the queue to be k. */
    MyCircularQueue(int k) {
        data.resize(k);
    }
    
    /** Insert an element into the circular queue. Return true if the operation is successful. */
    bool enQueue(int value) {
        if (isFull()) return false;
        data[(head + cnt) % data.size()] = value;
        ++cnt;
        return true;
    }
    
    /** Delete an element from the circular queue. Return true if the operation is successful. */
    bool deQueue() {
        if (isEmpty()) return false;
        head = (head + 1) % data.size();
        --cnt;
        return true;
    }
    
    /** Get the front item from the queue. */
    int Front() {
        return isEmpty() ? -1 : data[head];
    }
    
    /** Get the last item from the queue. */
    int Rear() {
        return isEmpty() ? -1 : data[(head + cnt - 1) % data.size()];
    }
    
    /** Checks whether the circular queue is empty or not. */
    bool isEmpty() {
        return cnt == 0;
    }
    
    /** Checks whether the circular queue is full or not. */
    bool isFull() {
        return cnt == data.size();
    }
private:
    vector<int> data;
    int cnt = 0, head = 0; // cnt: num of element in queue
};








































