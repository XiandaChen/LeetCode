class Solution {
public:
    int findLeastNumOfUniqueInts(vector<int>& arr, int k) {
        auto cmp = [](pair<int, int> &a, pair<int, int> &b) {
            return (a.second > b.second)
                || ((a.second == b.second) && (a.first < b.first));
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, 
                        decltype(cmp)> q(cmp);  // minHeap: num-freq
        unordered_map<int, int> m; // num-freq
        
        for (int a : arr) m[a]++;
        for (auto a : m) {
            q.push({a.first, a.second});
        }
        
        while (k > 0 && !q.empty()) {
            auto tmp = q.top(); q.pop();
            if (k - tmp.second < 0) {
                q.push({tmp.first, tmp.second - k});
                break;
            }
            else {
                k -= tmp.second;
            }
        }
        
        return q.size();
    }
};