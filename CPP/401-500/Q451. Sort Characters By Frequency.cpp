class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> m; 
        priority_queue<pair<int, char>> q; // maxHeap
        for (auto c : s) ++m[c];
        for (auto it : m) q.push({it.second, it.first});
        string res = "";
        while(!q.empty()) {
            auto t = q.top(); q.pop();
            res.insert(res.end(), t.first, t.second);
        }
        return res;
    }
};