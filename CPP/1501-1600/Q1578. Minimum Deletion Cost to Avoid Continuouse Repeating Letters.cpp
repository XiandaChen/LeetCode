class Solution {
public:
    int minCost(string s, vector<int>& cost) {
        int n = s.size(), res = 0;
        int sumCost = 0, maxCost = 0; // sum cost (max cost) for repeating letters
        
        for (int i = 0; i < n; i++) {
            if (i == 0 || s[i] != s[i - 1]) {
                // delete all repeating letters except the one with maxCost
                res += (sumCost - maxCost); 
                sumCost = maxCost = cost[i]; // for new char
            }
            else {
                sumCost += cost[i];
                maxCost = max(maxCost, cost[i]);
            }
        }
        
        res += sumCost - maxCost; // NOTE, for last repeating letters, "aabaa"
        
        return res;
    }
};