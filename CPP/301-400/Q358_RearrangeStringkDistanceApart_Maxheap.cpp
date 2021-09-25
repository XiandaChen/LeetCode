class Solution {
public:
    string rearrangeString(string s, int k) {
        if (k <= 1) return s; // corner case: s="a", k=0
        auto cmp = [](pair<char, int> & a, pair<char, int> & b) {
            return (a.second < b.second)
                || ((a.second == b.second) && (a.first > b.first));
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>,
                    decltype(cmp)> q(cmp); // maxHeap: char-freq
        unordered_map<char, int> m; // char-freq
        int len = s.size();
        string res = "";
        
        for (char c : s) m[c]++;
        for (auto a : m) q.push(a);
        
        while (!q.empty()) {
            // num of positions to be filled in
            int cnt = min(k, len);
            vector<pair<char, int>> tmp; 
            for (int i = cnt; i > 0; i--) {
                if (q.empty()) return ""; // not more distinct char
                auto t = q.top(); q.pop();
                res += t.first;
                if (--t.second) tmp.push_back(t);
                --len; // NOTE
            }
            
            for (auto a : tmp) q.push(a);
        }
        
        return res;
    }
};