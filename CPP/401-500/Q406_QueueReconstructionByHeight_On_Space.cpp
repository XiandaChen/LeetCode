class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int>> res;
        auto cmp = [](vector<int>& a, vector<int>& b) {
            return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]); // higher height first, or smaller k of same height first
        };
        sort(people.begin(), people.end(), cmp);
        for (auto p : people) {
            res.insert(res.begin() + p[1], p); // insert to corresponding position
        }
        return res;
    }
};