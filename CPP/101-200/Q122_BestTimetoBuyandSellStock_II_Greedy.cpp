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