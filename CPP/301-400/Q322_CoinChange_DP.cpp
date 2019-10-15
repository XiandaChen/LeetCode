class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1); // initial to amount+1, since minimum coin is 1
        dp[0] = 0; // need no coin for amount=0
        for (int i = 0; i <= amount; ++i) 
            for (int j = 0; j < (int)coins.size(); ++j)
                if (coins[j] <= i) 
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
        return (dp[amount] > amount) ? -1 : dp[amount]; // at most need amount coin_1 for amount
    }
};