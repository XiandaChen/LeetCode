class Solution {
public:
    vector<int> findBuildings(vector<int>& heights) {
        int n = heights.size(), curMax = 0;
        vector<int> maxRight(n), res;
        
        maxRight[n - 1] = 0;
        
        for (int i = n - 2; i >= 0; i--){
            curMax = max(curMax, heights[i + 1]);
            maxRight[i] = curMax;
        }
        
        for (int i = 0; i < n; i++) {
            if (heights[i] > maxRight[i]) res.push_back(i);
        }
        
        return res;
    }
};