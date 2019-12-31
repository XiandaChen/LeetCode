class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<long, vector<long>, greater<long>> q; // min heap
        q.push(1);
        for (int i = 1; i < n; ++i) {
            long t = q.top(); q.pop();
            while (!q.empty() && t == q.top()) q.pop(); // remove duplicates
            q.push(t * 2);
            q.push(t * 3);
            q.push(t * 5);
        }
        return q.top();
    }
};