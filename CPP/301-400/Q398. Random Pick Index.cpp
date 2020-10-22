class Solution {
public:
    Solution(vector<int>& nums) { val = nums; }
    int pick(int target) {
        int cnt = 0, res = -1;
        for (int i = 0; i < val.size(); ++i) {
            if (val[i] != target) continue;
            ++cnt;
            if (rand() % cnt == 0) res = i; // reservoir sampling
        }
        return res;
    }
private:
    vector<int> val;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * int param_1 = obj->pick(target);
 */

