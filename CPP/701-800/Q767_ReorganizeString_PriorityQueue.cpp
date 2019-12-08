class Solution {
public:
    string reorganizeString(string S) {
        map<char, int> m; // char-occurNum
        priority_queue<pair<int, char>> q; // max-heap, key=occurNum
        string res = "";
        for (char c : S) ++m[c];
        // construct max-heap
        for (auto a : m) {
            // some char occur more than half of the length
            if (a.second > (S.size() + 1) / 2) return ""; 
            q.push({a.second, a.first}); // or, q.push(make_pair(a.second, a.first)); 
        }
        while (q.size() >= 2) { // take two chars each time
            auto t1 = q.top(); q.pop();
            auto t2 = q.top(); q.pop();
            res += t1.second; // or, res.push_back(t1.second)
            res += t2.second;
            if (--t1.first) q.push(t1);
            if (--t2.first) q.push(t2);
        }
        // if one item left in the queue
        if (q.size() > 0) res += q.top().second;
        return res;
    }
};