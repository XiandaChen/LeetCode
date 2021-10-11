class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        auto cmp = [](pair<int, char> & a, pair<int, char> & b) { // maxHeap
            return a.first < b.first || (a.first == b.first && a.second > b.second);
        };
        priority_queue<pair<int, char>, vector<pair<int, char>>, decltype(cmp)> q(cmp);
        
        if (a > 0) q.push({a, 'a'});
        if (b > 0) q.push({b, 'b'});
        if (c > 0) q.push({c, 'c'});
            
        string res = "";
        
        // place the maximum value character 2 times and then its next smaller 1 time.
        while (!q.empty()) {
            auto cur = q.top(); q.pop();
            
            // add 2 characters as per round if possible
            for (int i = min(cur.first, 2); i > 0; i--) {
                res += cur.second;
                cur.first--;                
            }
            
            if (q.empty()) break;
            
            auto next = q.top(); q.pop();
            
            // if next char is the maxmium, i.e., next.first > cur.first
            // add two next.second if possible
            if (next.first >= cur.first) {
                res += next.second;
                next.first--;
            }
            if (next.first > 0) { // add the second next.second if possible
                res += next.second;
                next.first--;
            }
            
            if (cur.first) q.push(cur);
            if (next.first) q.push(next);
        }
        
        return res ; 
    }
};