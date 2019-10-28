class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if (prices.empty()) return 0;
        int n = prices.size(), k = 3; // k = 3 for two transactions
        vector<vector<int>> global(n, vector<int>(k, 0)), local(n, vector<int>(k, 0));
        for (int i = 1; i < n; ++i) {
            int diff = prices[i] - prices[i - 1];
            for (int j = 1; j < k; ++j) {
                local[i][j] = max(global[i - 1][j - 1], local[i - 1][j]) + diff;
                global[i][j] = max(local[i][j], global[i - 1][j]);
            }
        }
        return global.back().back();
    }
};