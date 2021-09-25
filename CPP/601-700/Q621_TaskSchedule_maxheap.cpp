class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        auto cmp = [](pair<char, int> & a, pair<char, int> & b) {
            return (a.second < b.second)
                || ((a.second == b.second) && (a.first > b.first));
        };
        priority_queue<pair<char, int>, vector<pair<char, int>>,
                    decltype(cmp)> q(cmp); // maxHeap: task-num
        unordered_map<char, int> m; // task-num
        string res = "";
        
        for (char c : tasks) m[c]++;
        for (auto a : m) q.push(a);
        
        while (!q.empty()) {
            vector<pair<char, int>> tmp;
            
            for (int i = n + 1; i > 0; i--) { // NOTE, cycle: n+1
                if (q.empty()) {
                    res += '#'; // no distinct char, add 'idle'
                }
                else {
                    auto t = q.top(); q.pop();
                    res += t.first;
                    if (--t.second) tmp.push_back(t);
                    
                    // the very last task
                    if (t.second == 0 && tmp.empty() && q.empty()) break;
                }
            }
            
            for (auto a : tmp) q.push(a); // remaining tasks
        }
        
        return res.size();
    }
};