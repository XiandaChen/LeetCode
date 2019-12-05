class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> dic;
        for (int i = 0; i < order.size(); ++i) dic[order[i]] = i; // alien dict order
        for (int i = 1; i < words.size(); ++i) {
            int l1 = words[i - 1].size(), l2 = words[i].size(), j = 0;
            for (; j < min(l1, l2); ++j) {
                if (dic[words[i - 1][j]] < dic[words[i][j]]) break; // if first-ch smaller
                else if (dic[words[i - 1][j]] > dic[words[i][j]]) return false;
            }
            if (j == min(l1, l2) && l1 > l2) return false; // check input: ["apple","app"]
        }
        return true;
    }
};