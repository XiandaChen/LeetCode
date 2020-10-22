class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
        auto cmp = [](vector<int> &a, vector<int> &b){
            return a[0] + a[1] < b[0] +b[1]; // maxHeap
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        vector<vector<int>> res;
        for (int i = 0; i < min((int)nums1.size(), k); ++i) { // trim, only firt k elements
            for (int j = 0; j < min((int)nums2.size(), k); ++j) {
                if (q.size() < k) {
                    // q.push(vector<int>(nums1[i], nums2[j]));  // error: vector<int> v(1, 10) => v=[10]
                    q.push(vector<int>{nums1[i], nums2[j]});    // vector<int> v{1, 10} => v = [1, 10]
                }
                else if (nums1[i] + nums2[j] < q.top()[0] + q.top()[1]) {
                    // new pair with sum smaller than heap top
                    q.pop();  // to maintain only k elements in heap
                    q.push(vector<int>{nums1[i], nums2[j]});
                }
            }
        }
        
        while (!q.empty()) {
            res.push_back(q.top()); q.pop();
        }
        return res;
    }
};
