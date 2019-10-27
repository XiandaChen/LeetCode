class Solution {
public:
    vector<vector<int>> kClosest(vector<vector<int>>& points, int K) {
        vector<vector<int>> res;
        auto cmp = [](vector<int> & a, vector<int> & b) {
            return a[0] * a[0] + a[1] * a[1] > b[0] * b[0] + b[1] * b[1]; // min-queue
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        for (auto point : points)
            q.push(point);
        for (int i = 0; i < K; ++i) {
            res.push_back(q.top());
            q.pop();
        }
        return res;
    }
};