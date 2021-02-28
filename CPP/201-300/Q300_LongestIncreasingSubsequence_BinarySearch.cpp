class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty()) return 0;
        vector<int> subnums{nums[0]};
        for (int a : nums) {
            if (a < subnums[0]) { // switch the smallest one
                subnums[0] = a;
            }
            else if (a > subnums.back()) { // add larger ones
                subnums.push_back(a);
            }
            else {
                int left = 0, right = subnums.size();
                while (left < right) { // change the first num that no-less than a
                    int mid = left + (right - left) / 2;
                    if (subnums[mid] < a) left = mid + 1;
                    else right = mid;
                }
                subnums[right] = a;
            }
        }
        return subnums.size();
    }
};