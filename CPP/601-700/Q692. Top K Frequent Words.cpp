class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> m; // word-count
        auto cmp = [](pair<int, string> &a, pair<int, string> &b) { // max
            return a.first < b.first || (a.first == b.first && a.second > b.second); // <: int; >: string
        };
        priority_queue<pair<int, string>, vector<pair<int, string>>, decltype(cmp)> q(cmp); // maxheap: count-word
        for (auto word : words) ++m[word];
        for (auto it : m) q.push({it.second, it.first});
        vector<string> res;
        for (int i = k; i > 0; --i) {
            res.push_back(q.top().second);
            q.pop();
        }
        return res;
    }
};