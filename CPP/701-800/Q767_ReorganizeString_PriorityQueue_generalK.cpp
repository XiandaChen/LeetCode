class Solution {
public:
    string reorganizeString(string s) {
        int len = s.size(), k = 2;
        map<char, int> m;
        priority_queue<pair<int, char>> q;
        string res = "";
        for (char c : s) ++m[c];
        for (auto a : m)  q.push({a.second, a.first});
        while (!q.empty()) {
            vector<pair<int, char>> tmp; // to hold availabel items after processing
            int cnt = min(k, len); // take k item each time if len>=k
            for (int i = 0; i < cnt; ++i) {
                if (q.empty()) return ""; // check
                auto t = q.top(); q.pop();
                res += t.second;
                if (--t.first) tmp.push_back(t);
                --len;
            }
            for (auto a : tmp) q.push(a);
        }
        return res;
    }
};