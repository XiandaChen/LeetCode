class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.empty()) return 0;
        int pre = 0, cur = 1, n = nums.size();
        bool flag = false;
        while (cur < n) {
            if (nums[pre] == nums[cur]) {
                if (!flag)  { // first time repeating
                    flag = true;
                    nums[++pre] = nums[cur++];
                }
                else ++cur; // repeat more than twice
            }
            else {
                flag = false;
                nums[++pre] = nums[cur++];
            }
        }
        return pre + 1;
    }
};

