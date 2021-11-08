// 136. Single Number
// Input: [4,1,2,1,2];   Output: 4
// BitManuplation: Time O(N), Space O(1); unordered_map: Space O(N)
class Solution { // bit manuplation
public:
    int singleNumber(vector<int>& nums) {
        int res = 0;
        for (int num : nums) res ^= num;
        return res;
    }
};
class Solution { // unordered_map
public:
    int singleNumber(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (int num : nums) mp[num] += 1;
        for (auto x : mp)
            if (x.second == 1) return x.first;
        return -1;
    }
};
// 137. Single Number II
// Input: [0,1,0,1,0,1,99];   Output: 99
class Solution {
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
// 260. Single Number III
// Input:  [1,2,1,3,2,5];  Output: [3,5]
class Solution {
public:
    vector<int> singleNumber(vector<int>& nums) {
        // [1,2,1,3,2,5] => diff=3^5='110', i.e., difference at 2nd and 3rd bit
        // int diff = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        // int diff = 0;
		long diff = 0; // in case of input [1,1,0,-2147483648]
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

// 287. Find the Duplicate Number
// Input: nums = [1,3,4,2,2]; Output: 2
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int res = 0, n = nums.size();
        
        for (int i = 0; i < 32; i++) {
            int bit = (1 << i), cnt1 = 0, cnt2 = 0;
            
            for (int k = 0; k < n; k++) {
                if ((k & bit) > 0) cnt1++;
                if ((nums[k] & bit) > 0) cnt2++;
            }
            
            if (cnt2 > cnt1) res += bit;
        }
        
        return res;
    }
};

// 371. Sum of Two Integers
// 759+674
// no considering carry: 323; consideirng carry: 1110
// (759+674) = (323 + 1110)
class Solution {
public:
    int getSum(int a, int b) {
        if (b == 0) return a;
        
        int sum = a ^ b;
        int carry = (a & b & 0x7fffffff) << 1;
        
        return getSum(sum, carry);
    }
};