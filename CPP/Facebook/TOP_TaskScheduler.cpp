class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        if (n == 0) return tasks.size();
        unordered_map<char, int> m; // char-freq
        auto cmp = [] (pair<char, int>&a, pair<char, int>&b) {
            return a.second < b.second || (a.second == b.second && a.first > b.first);};
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> q(cmp);        
        for (char c : tasks) ++m[c];
        for (auto a : m) q.push(a); 
        int res = 0, cycle = n + 1;
        while (!q.empty()) {
            int cnt = 0;   vector<pair<char, int>> tmp;
            for (int i = cycle; i > 0; --i) {
                if (q.empty()) break; // no distint char to pad
                auto t = q.top(); q.pop();
                ++cnt; // pad this task
                if (--t.second) tmp.push_back(t);            }
            for (auto a : tmp) q.push(a);
            // q.empty()=> the last round
            res += q.empty() ? cnt : cycle;        }
        return res;
    }
};