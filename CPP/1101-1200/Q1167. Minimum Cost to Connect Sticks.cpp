class Solution {
public:
    int connectSticks(vector<int>& sticks) {
        if (sticks.size() < 2) return 0;
        
        priority_queue<int, vector<int>, greater<int>> q;
        
        for (int s : sticks) q.push(s);
        
        int res = 0;
        while (q.size() > 1) {
            int a = q.top(); q.pop();
            int b = q.top(); q.pop();
            int c = a + b;
            res += c;
            q.push(c);
        }
        
        return res;
    }
};