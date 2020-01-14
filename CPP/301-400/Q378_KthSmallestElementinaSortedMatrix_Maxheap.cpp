class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        priority_queue<int> q; // max-heap
        for (int i = 0; i < matrix.size(); ++i) {
            for (int j = 0; j < matrix[0].size(); ++j) {
                q.push(matrix[i][j]);
                if (q.size() > k) q.pop(); // remove element after kth larger value
            }
        }
        return q.top();
    }
};