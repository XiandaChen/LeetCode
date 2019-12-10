class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int pre = 0, cur = 0, n = nums.size();
        while (cur < n) {
            // move cur forward when encountering duplicate num
            if (nums[pre] == nums[cur]) ++cur;
            else nums[++pre] = nums[cur++]; // increment pre
        }
        return pre + 1;
    }
};