class Solution {
public:
    string alienOrder(vector<string>& words) {
        unordered_set<char> chars; // store all chars in given words
        set<pair<char, char>> st; // store order pairs
        vector<int> indegree(128); // here assume first 128 ASCII
        queue<char> q; // to hold zero-indegree node, and BFS traverse the graph
        string res;
        
        for (string w : words) chars.insert(w.begin(), w.end()); // get all chars in given words
        for (int i = 0; i < words.size() - 1; ++i) { // find all order pairs
            int mn = min(words[i].size(), words[i + 1].size());
            for (int j = 0; j < mn; ++j) {
                if (words[i][j] != words[i + 1][j]) { // diff chars b/w two near words
                    st.insert(make_pair(words[i][j], words[i + 1][j]));
                    break; // dont forget
                }
            }
        }
        for (auto a : st) ++indegree[a.second]; // indegree for chars
        for (auto ch : chars) { // add chars of indegree=zero to queue, that is traversed first
            if (indegree[ch] == 0) {
                q.push(ch);
                res.push_back(ch);
            }
        }
        while (!q.empty()) { // BFS traverse the graph from zero-indegree char
            char ch = q.front(); q.pop();
            for (auto a : st) { // check if ch is in the set st
                if (ch == a.first) {
                    --indegree[a.second];
                    if (indegree[a.second] == 0) {
                        q.push(a.second);
                        res.push_back(a.second);
                    }
                }
            }
        }
        return res.size() == chars.size() ? res : "";
    }
};