class Solution {
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        sort(horizontalCuts.begin(), horizontalCuts.end());
        sort(verticalCuts.begin(), verticalCuts.end());
        
        const int mod=1e9+7;
        int m = horizontalCuts.size(), n = verticalCuts.size();
        int maxHeight = horizontalCuts[0], maxWidth = verticalCuts[0];
        
        for (int i = 1; i < m; i++) 
            maxHeight = max(maxHeight, horizontalCuts[i] - horizontalCuts[i - 1]);
        maxHeight = max(maxHeight, h - horizontalCuts[m - 1]);
        
        for (int i = 1; i < n; i++) 
            maxWidth = max(maxWidth, verticalCuts[i] - verticalCuts[i - 1]);
        maxWidth = max(maxWidth, w - verticalCuts[n - 1]);
        
        // in case h=1000000000, w=1000000000, [2], [2]
        long long int mH = maxHeight, mW = maxWidth;  
        
        return (mH * mW) % mod;
    }
};