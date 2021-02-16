class Solution {
public:
    string largestNumber(vector<int>& nums) {
        auto cmp = [](int a, int b){
            return to_string(a) + to_string(b) > to_string(b) + to_string(a);
        };
        sort(nums.begin(), nums.end(), cmp); // a=9, b=34, 934>349
        string res;
        for (int i = 0; i < nums.size(); ++i)
            res += to_string(nums[i]);
        return res[0] == '0' ? "0" : res;
    }
};