class Solution {
public:
    int bitwiseComplement(int N) {
        if (N == 0) return 1;
        int bitcount = 0, tmp = N;
        while (tmp > 0) {
            ++bitcount; 
            tmp >>= 1;
        }
        int all_bit_set = pow(2, bitcount) - 1;
        return N ^ all_bit_set;
    }
};