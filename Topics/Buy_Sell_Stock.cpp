//  121. Best Time to Buy and Sell Stock
// at most one transaction
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0, buy = INT_MAX;
        for (int price : prices) {
            buy = min(buy, price);  // min buy-price untill now
            res = max(res, price - buy); // update maxprofit
        }
        return res;
    }
};

// 122. Best Time to Buy and Sell Stock II
// as many transactions as you like
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int res = 0;
		// must be (int) in for loop in case of input []
		// or, define int res = 0, n = prices.size();
        // 		      for (int i = 0; i < - 1; ++i) 
        for (int i = 0; i < (int)prices.size() - 1; ++i) { 
            if (prices[i] < prices[i + 1])
                res += prices[i + 1] - prices[i];
        }
        return res;
    }
};

// 123. Best Time to Buy and Sell Stock III (DP)
// at most two transactions.
// local[i,j]: maxprofit when complete at most j transactions till day i, 
//			and the last transaction is completed on day id
// global[i,j]: maxprofit when complete at most j transactions till day i
// local[i][j] = max(global[i - 1][j - 1], local[i - 1][j]) + diff
// {original: local[i][j] = max(global[i - 1][j - 1] + max(diff, 0), local[i - 1][j] + diff)}
// global[i][j] = max(local[i][j], global[i - 1][j])
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


// 188. Best Time to Buy and Sell Stock IV (DP)
// at most k transactions.
class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        if (prices.empty()) return 0;
        if (k >= prices.size()) return maxProfit(prices); // tricked, must
        int n = prices.size();
        vector<vector<int>> global(n, vector<int>(k + 1, 0)), local(n, vector<int>(k + 1, 0));
        for (int i = 1; i < n; ++i) {
            int diff = prices[i] - prices[i - 1];
            for (int j = 1; j <= k; ++j) {
                local[i][j] = max(global[i - 1][j - 1], local[i - 1][j]) + diff;
                global[i][j] = max(local[i][j], global[i - 1][j]);
            }
        }
        return global.back().back();
    }
    int maxProfit(vector<int> & prices) { // Q122. as many transactions as you like
        if (prices.empty()) return 0;
        int res = 0;
        for (int i = 0; i < (int) prices.size() - 1; ++i) {
            if (prices[i] < prices[i + 1])
                res += prices[i + 1] - prices[i];
        }
        return res;
    }
};

// 309. Best Time to Buy and Sell Stock with 1-day Cooldown
// Actions: you have 1 stock and you sell it
// 			you have 1 stock and you do nothing
// 			you have 0 stock and you buy stock i
// 			you have 0 stock and you do nothing
// Transictions: action at day-i depends on day-(i-1)
// 		if you take action 1 on day i 
// 		==> you have either taken action 2 or 3 on day i-1
// 		if you take action 2 on day i 
// 		==> you have either taken action 2 or 3 on day i-1
// 		if you take action 3 on day i 
// 		==> you must have taken action 4 on day i-1 (you can not sell on day i-1 due to cool down)
// 		if you take action 4 on day i 
//		==> you have either taken action 1 or 4 on day i-1
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int L = prices.size();
        if(L < 2) return 0;
        
        // profit at day-i
        int has1_Sell = 0;  // action: have stock and sell it
        int has1_doNothing = -prices[0];  // have stock and do nothing
        int has0_Buy = -prices[0];      // have no stock and buy it
        int has0_doNothing = 0;         // have no stock and do nothing
        for(int i = 1; i < L; ++i) {
            has1_doNothing = has1_doNothing > has0_Buy ? has1_doNothing : has0_Buy;
            has0_Buy = -prices[i] + has0_doNothing;
            has0_doNothing = has0_doNothing > has1_Sell ? has0_doNothing : has1_Sell;
            has1_Sell = prices[i] + has1_doNothing;
        }
        return has1_Sell > has0_doNothing ? has1_Sell : has0_doNothing;
    }
};
