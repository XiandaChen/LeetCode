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