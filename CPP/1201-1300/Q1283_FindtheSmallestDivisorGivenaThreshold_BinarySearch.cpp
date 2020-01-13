class Solution {
public:
    int smallestDivisor(vector<int>& nums, int threshold) {
        int left = 1, right = * max_element(nums.begin(), nums.end()); // #include <algorithm>
        while (left < right) {
            int mid = left + (right - left) / 2;
            int _sum = 0;
            for (auto num : nums) 
                _sum += (num + (mid - 1)) / mid;  // rounded to int greater than or equal to
            if (_sum > threshold) left = mid + 1; // increase divisor if sum larger than threshold
            else right = mid;
        }
        return left;
    }
};