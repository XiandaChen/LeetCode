class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> m;
        priority_queue<pair<int, int>> q; // int is not struct for queue, use pair<>
        vector<int> res;
        for (auto num : nums) ++m[num];  // use auto, int is not struct
        for (auto it : m) q.push({it.second, it.first}); // use auto, int is not struct
        for (int i = 0; i < k; ++i) {
            res.push_back(q.top().second);
            q.pop();
        }
        return res;
    }
};