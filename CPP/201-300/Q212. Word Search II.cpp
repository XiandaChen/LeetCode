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


