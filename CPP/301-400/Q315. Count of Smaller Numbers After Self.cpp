class Solution {    
public:
    vector<int> countSmaller(vector<int>& nums) {        
        int n = nums.size();
        if (n == 0) return {};
        
        vector<int> sortedNums = nums;        
        vector<int> counts(n,0);
        DivideConque(nums,sortedNums, counts, 0, n - 1); 
        return counts;
    }
    
    void DivideConque(vector<int>& nums, vector<int>& sortedNums, 
                      vector<int>& counts, int start, int end){
        if (start == end) return;
        
        // divide: sort each part
        int mid = start + (end - start) / 2;
        DivideConque(nums, sortedNums, counts, start, mid);
        DivideConque(nums, sortedNums, counts, mid + 1, end);
        
        // since nums[start, mid] and nums[mid + 1, end] are sorted
        // for each num in [start, mid], we know how many num in [mid + 1, end] less than it
        for (int i = start; i <= mid; i++) {
            auto pos = lower_bound(sortedNums.begin() + mid + 1, 
                                   sortedNums.begin() + end + 1, nums[i]);            
            counts[i] += pos - (sortedNums.begin() + mid + 1);
        }
        
        // here use sort(), but implemented as mergesort can be more faster        
        sort(sortedNums.begin() + start, sortedNums.begin() + end + 1);  
    }
};
