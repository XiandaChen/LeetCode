class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) { // input is char's
        if (matrix.empty()) return 0;
        int m = matrix.size(), n = matrix[0].size(), res = 0;
        vector<vector<int>> dp(m, vector<int>(n, 0)); // initial to 0
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i == 0 || j == 0) dp[i][j] = matrix[i][j] - '0'; // char
                else if (matrix[i][j] == '1') 
                    dp[i][j] = min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]) + 1;
                res = max(res, dp[i][j]);
            }
        }
        return res * res; // res: length of square edge
    }
};