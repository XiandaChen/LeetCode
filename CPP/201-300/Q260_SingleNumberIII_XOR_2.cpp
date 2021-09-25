class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        int n1xn2 = 0;
        for (int num : nums) n1xn2 ^= num;
        
        // rightMostSetBit: to partition all nums into two groups
        // one has num1 (ith bit of 0) and the other has num2 (ith bit of 1)
        int rightMostSetBit = 1;
        while ((rightMostSetBit & n1xn2) == 0) {
            rightMostSetBit <<= 1;  // right shift by one
        }
        
        int num1 = 0, num2 = 0;
        for (int num : nums) {
            if ((num & rightMostSetBit) == 0) { // ith bit in num has value of 0
                num1 ^= num;
            }
            else { // ith bit in num has value of 1
                num2 ^= num;  
            } 
        }
        
        return {num1, num2};
    }
};