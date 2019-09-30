class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        unordered_set<int> s;
        int maxval;
        for (int num : nums) {
            if (num < 0) continue;
            s.insert(num);
            maxval = max(maxval, num);
        }
        for (int i = 1; i <= maxval; i++)
            if (!s.count(i)) return i;
        return maxval + 1;
    }
};