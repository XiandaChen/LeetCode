class Solution {
public:
    int numSubarrayProductLessThanK(vector<int>& nums, int k) {
        int res = 0, left = 0, subproduct = 1; // subwindow of product < k
        for (int i = 0; i < (int)nums.size(); ++i) {
            subproduct *= nums[i];
            while (left <= i && subproduc >= k) {
                subproduc /= nums[left++]; // move subwindow to right
            }
            res += i - left + 1; // subwindow length: [5,2,6] => [6],[2,6],[5,2,6]
        }
    }
};