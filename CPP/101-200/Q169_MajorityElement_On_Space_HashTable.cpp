class Solution {
public:
    int majorityElement(vector<int>& nums) {
        unordered_map<int, int> mp;
        for (auto num : nums) ++mp[num];
        int val = mp.begin()->first, cnt = mp.begin()->second;
        for (unordered_map<int, int>:: iterator it = mp.begin(); it != mp.end(); it++) {
            if (it->second > cnt) {
                val = it->first;
                cnt = it->second;
            }
        }
        return val;
    }
};