class Solution {
public:
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<char, int> dic;
        for (int i = 0; i < order.size(); ++i) dic[order[i]] = i;
        for (int i = 1; i < (int)words.size(); ++i)
            if (!isAlienSorted(words[i - 1], words[i], dic)) return false;
        return true;
    }
    bool isAlienSorted(string s1, string s2, unordered_map<char, int> & dic) {
        int l1 = s1.size(), l2 = s2.size();
        for (int i = 0; i < min(l1, l2); ++i) {
            if (dic[s1[i]] > dic[s2[i]]) return false;
            else if (dic[s1[i]] < dic[s2[i]]) return true;
        }
        if (l2 == min(l1, l2)) return false;
        return true;
    }
};