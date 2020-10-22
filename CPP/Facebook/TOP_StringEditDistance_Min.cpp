class Solution {
public:
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        // memo[i][j]: num operations for word1[i:m] and word2[j:n]
        vector<vector<int>> memo(m, vector<int>(n, 0)); 
        return minDistance(word1, 0, word2, 0, memo);
    }
    int minDistance(string word1, int i, string word2, int j, vector<vector<int>> &memo) {
        if (i == word1.size()) return (int)word2.size() - j;
        if (j == word2.size()) return (int)word1.size() - i;
        if (memo[i][j] > 0) return memo[i][j];
        if (word1[i] == word2[j]) {
            return minDistance(word1, i + 1, word2, j + 1, memo);
        }
        else {
            int insertCnt = minDistance(word1, i, word2, j + 1, memo);
            int deleteCnt = minDistance(word1, i + 1, word2, j, memo);
            int replaceCnt = minDistance(word1, i + 1, word2, j + 1, memo);
            memo[i][j] = min(insertCnt, min(deleteCnt, replaceCnt)) + 1;
        }
        return memo[i][j];
    }
};