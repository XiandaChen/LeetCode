class Solution {
public:
    int maxSideLength(vector<vector<int>>& mat, int threshold) {
        if (mat.empty() || mat[0].empty()) return 0;
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        for (int i = 1; i <= m; ++i) 
            for (int j = 1; j <= n; ++j) 
                // dp[0][j]=0, dp[i][0]=0, dp[i][j]=..+mat[i-1][j-1]
                dp[i][j] = dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1] + mat[i - 1][j -1];
        // auto sumRegion = [] (int x1, int y1, int x2, int y2, vector<vector<int>> & dp) {
        //     return dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 -1][y1 - 1];
        // };
        auto sumRegion = [&] (int x1, int y1, int x2, int y2) { // '&' to use dp variable
            return dp[x2][y2] - dp[x2][y1 - 1] - dp[x1 - 1][y2] + dp[x1 -1][y1 - 1];
        };
        
        int res = 0;
        // binary search
        for (int x = 1; x <= m; ++x) {
            for (int y = 1; y <= n; ++y) {
                int left = 0, right = min(m - x, n - y) + 1;
                while (left < right) {
                    int mid = left + (right - left) / 2;
                    // find smallest left such that > threshold
                    if (sumRegion(x, y, x + mid, y + mid) > threshold) right = mid;
                    else left = mid + 1;
                }
                res = max(res, left);
            }
        }
        return res;
    }
};