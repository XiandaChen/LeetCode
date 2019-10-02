class Solution {
public:
    void sortColors(vector<int>& nums) {
        vector<int> color(3);
        for (auto num : nums)
            ++color[num];
        for (int i = 0, cur = 0; i < 3; ++i) {
            for(int j = 0; j < color[i]; ++j) {
                nums[cur++] = i;
            }
        }
    }
};