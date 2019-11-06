class Solution {
public:
    int longestArithSeqLength(vector<int>& A) {
        if (A.size() <= 1) return A.size();
        unordered_map<int, unordered_map<int, int>> dp;
        int res = 0;
        for (int i = 0; i < (int)A.size(); ++i) {
            for (int j = 0; j < i; ++j) {
                int diff = A[i] - A[j];
                if(!dp[diff].count(i)) dp[diff][i] = 2;
                dp[diff][i] = max(dp[diff][j] + 1, dp[diff][i]);
                res = max(res, dp[diff][i]);
            }
        }
        return res;
    }
};