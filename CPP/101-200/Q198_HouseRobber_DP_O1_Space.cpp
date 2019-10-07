class Solution {
public:
    int rob(vector<int>& nums) {
        int robEven = 0, robOdd = 0;
        for (int i = 0; i < nums.size(); ++i) {
            if (i % 2 == 0) 
                robEven = max(robEven + nums[i], robOdd);
            else
                robOdd = max(robOdd + nums[i], robEven);
        }
        return max(robEven, robOdd);
    }
};