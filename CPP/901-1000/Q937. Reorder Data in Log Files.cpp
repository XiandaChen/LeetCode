class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> res, digitLogs;
        vector<vector<string>> letterLogs; // {identifier, contents}
        
        for (string log: logs) {
            auto pos = log.find(" ");
            if (isdigit(log[pos + 1])) {
                digitLogs.push_back(log); continue;
            }
            letterLogs.push_back({log.substr(0, pos), log.substr(pos + 1)});
        }
        
        // sorted lexicographically by their contents. 
        // for same contents, then sort them lexicographically by their identifiers.
        auto cmp = [](vector<string> &a, vector<string> &b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);
        };
        sort(letterLogs.begin(), letterLogs.end(), cmp);
        
        for (auto &a : letterLogs) {
            res.push_back(a[0] + " " + a[1]);
        }
        
        // digit-logs maintain their relative ordering.
        for (auto &a : digitLogs) {
            res.push_back(a);
        }
        
        return res;
    }
};