class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int res = 0, cycle = n + 1;
        unordered_map<char, int> m; 
        auto cmp = [](pair<char, int> &a, pair<char, int> &b){
            return a.second < b.second || (a.second == b.second && a.first > b.first);
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> q(cmp); // maxHeap: freq
        for (auto c : tasks) ++m[c];
        for (auto it : m) q.push(it);
        
        while (!q.empty()) {
            vector<pair<char, int>> tmp;
            int cnt = 0;
            for (int i = cycle; i > 0; --i) { // each cycle, insert idle periods if not distinct task
                if (!q.empty()) {
                    auto t = q.top(); q.pop();
                    ++cnt;
                    if (--t.second > 0) tmp.push_back(t);
                }
            }
            for (auto a : tmp) q.push(a);
            res += q.empty() ? cnt : cycle; // for the last cycle, not need to insert idle periods at the end
        }
        return res;
    }
};