class Solution {
public:
    int findComplement(int num) {
        int bitcount = 0, tmp = num;
        while (tmp > 0) {
            ++bitcount;
            tmp = tmp >> 1;
        }
        // 7 = 8 - 1 = 2^3 - 1
        int all_bit_set = pow(2, bitcount) - 1;
        // 101 ^ 010 = 111 (all_bit_set)
        return num ^ all_bit_set;
    }
};