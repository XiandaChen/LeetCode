vclass Solution {
public:
    int singleNumber(vector<int>& nums) {
        int res = 0; // 32-bit num
        // add up value of each bit pos of nums, then mod to 3
        for (int i = 0; i < 32; ++i) {
            int sum = 0;
            for (int num : nums)
                sum += (num >> i) & 1; // i-th bit value
            res |= (sum % 3) << i; // num of ith-bit=1 appears three times
        }
        return res;
    }
};