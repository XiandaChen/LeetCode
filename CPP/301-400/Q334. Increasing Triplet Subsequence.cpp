class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int min1 = INT_MAX, min2 = INT_MAX;
        for (int num : nums) {
            if (num > min2) return true;
            else if (num < min1) min1 = num;
            else if (min1 < num && num < min2) min2 = num;
        }
        return false;
    }
};