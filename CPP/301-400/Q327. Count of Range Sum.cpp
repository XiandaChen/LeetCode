// 327. Count of Range Sum
// Input: nums = [-2,5,-1], lower = -2, upper = 2
// Output: 3; ranges: 0,0], [2,2], and [0,2] and their respective sums are: -2, -1, 2.
// Time: O(nlog(n)); Space: O(n)
class Solution {
public:
// function counts the ranges with sum greater than or equal to k
    int countAndSort(vector<long>::iterator begin, vector<long>::iterator end, int k) {
	// if subarray contains a single element
        if(begin + 1 == end) return (*begin >= k);
        
        auto mid = begin + (end - begin) / 2;
        int res = countAndSort(begin, mid, k) + countAndSort(mid, end, k);
        
        for(auto i = begin, j = mid; i != mid; ++i) {
		// we know that if the value of (j - i) >= k, then for all greater values of j this condition will hold until
		// i is increased, as both the arrays are sorted
            while(j != end && (long)*j - (long)*i < (long)k)
                j++;
            res += (end - j);
        }
        inplace_merge(begin, mid, end);

        return res;
    }
    
	// calling the main function with a copy of prefix sum array
    int countGreaterThanK(vector<long> nums, int k) {
        return countAndSort(nums.begin(), nums.end(), k);
    }
    
    int countRangeSum(vector<int>& nums, int lower, int upper) {
        int n = nums.size();
        vector<long> prefix(n, 0);
        prefix[0] = nums[0];
        // generating prefix sum array
        for(int i = 1; i < n; ++i)
            prefix[i] += prefix[i - 1] + nums[i];
			
        return countGreaterThanK(prefix, lower) - countGreaterThanK(prefix, upper + 1);
    }
};
