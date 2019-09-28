class Solution {
public:
    int trap(vector<int>& height) {
        if (!height.size()) return 0;
        int res = 0, size = height.size();
        vector<int> leftmax(size, 0), rightmax(size, 0);
        // leftmax from left end upto index i
        leftmax[0] = height[0];
        for (int i = 1; i < size - 1; i++) 
            leftmax[i] = max(leftmax[i - 1], height[i]);
        // rightmax from right end upto index i
        rightmax[size - 1] = height[size - 1];
        for (int i = size - 2; i >= 0; i--)
            rightmax[i] = max(rightmax[i + 1], height[i]);
        for (int i = 0; i < size - 1; i++)
            res += min(leftmax[i], rightmax[i]) - height[i];
        return res;
    }
};