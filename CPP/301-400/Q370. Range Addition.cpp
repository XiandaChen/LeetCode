class Solution {
public:
    vector<int> getModifiedArray(int length, vector<vector<int>>& updates) {
        vector<int> res, nums(length + 1, 0); // length+1: in case idx (end+1)==length
        
        // updates[i] = [startIdx_i, endIdx_i, inc_i]
        // nums[startIdx_i, endIdx_i] += inc_i; and then nums[startIdx_i+1,:] -= inc_i
        for (auto & a: updates) {
            nums[a[0]] += a[2];  // accumulate sum from startIdx_i will add inc_i to [startIdx_i, :]
            nums[a[1] + 1] -= a[2]; // accumulate sum from startIdx_i+1 will remove inc_i from [startIdx_i+1, :]
        }
        
        int sum = 0;
        for (int i = 0; i < length; ++i) {
            sum += nums[i];
            res.push_back(sum);
        }
        
        return res;
    }
};