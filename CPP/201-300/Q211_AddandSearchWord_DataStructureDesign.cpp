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

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */