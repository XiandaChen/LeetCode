class Solution {
public:
    int trap(vector<int>& height) {
        int res = 0, left = 0, right = height.size() - 1;
        while (left < right) {
            int boundbar = min(height[left], height[right]);
            if (boundbar == height[left]) {
                left++;
                while (left < right && height[left] < boundbar) 
                    res += boundbar - height[left++];            }
            else {
                right--;
                while (left < right && height[right] < boundbar)
                    res += boundbar - height[right--];            }
        }
        return res;
    }
};