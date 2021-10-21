class Solution {
public:
    vector<string> mostVisitedPattern(vector<string>& username, vector<int>& timestamp, vector<string>& website) {
        unordered_map<string, map<int, string>> userData; // user-<time, web>, map sorted by time
        unordered_map<string, int> sequenceCount; // pattern-cnt
        int n = username.size(), maxCount = 0;
        string res = "";
        
        // user visit logs
        for (int i = 0; i < n; i++) {
            userData[username[i]][timestamp[i]] = website[i];
        }
        
        // collect pattern, i.e., three sequence
        for (auto data : userData) {
            unordered_set<string> sequences; // set to remove duplicates
            for (auto it1 = data.second.begin(); it1 != data.second.end(); it1++) {
                for (auto it2 = next(it1); it2 != data.second.end(); it2++) {
                    for (auto it3 = next(it2); it3 != data.second.end(); it3++) {
                        sequences.insert(it1->second + "$" + it2->second + "#" + it3->second);
                    }
                }
            }
            
            for (auto seq: sequences) sequenceCount[seq]++;
        }
        
        // find sequence with longest count
        for (auto seq : sequenceCount) {
            if (res == "" || seq.second > maxCount) {
                res = seq.first;
                maxCount = seq.second;
            }
            else if (seq.second == maxCount) {
                res = min(res, seq.first);
                maxCount = seq.second;
            }
        }
        
        auto pos1 = res.find("$");
        auto pos2 = res.find("#");
        
        return {res.substr(0, pos1), res.substr(pos1 + 1, pos2 - pos1 - 1), res.substr(pos2 + 1)};
    }
};