class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        // [1,2,1,3,2,5] => diff=3^5='110', i.e., difference at 2nd and 3rd bit
        // int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        int diff = 0;
        for (int num : nums) diff ^= num;
        // split '110' into '100' and '010'
        int mask = diff & -diff;  // numder of rightmost set bit, '10'
        vector<int> res(2, 0);
        for (int num : nums) {
            if (num & mask) res[0] ^= num;
            else res[1] ^= num;
        }
        return res;
    }
};