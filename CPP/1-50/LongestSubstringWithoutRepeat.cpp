class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map <char, int> umap;
        int len = s.length(), ans = 0;
        for (int i = 0, j = 0; j < len; j++) {
            if (umap.find(s.at(j)) != umap.end()) { // char in hashmap
                i = (umap[s.at(j)] > i) ? umap[s.at(j)] : i;
            }
            ans = ((j - i + 1) > ans) ? (j - i + 1) : ans;
            umap[s.at(j)] = j + 1;
        }
        return ans;
    }
};