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