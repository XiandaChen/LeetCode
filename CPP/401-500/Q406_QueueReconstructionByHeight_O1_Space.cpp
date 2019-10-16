class Solution {
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        auto cmp = [](vector<int>& a, vector<int>& b) {
            return a[0] > b[0] || (a[0] == b[0] && a[1] < b[1]); // higher height first, or smaller k of same height first
        };
        sort(people.begin(), people.end(), cmp);
        for (int i = 0; i < (int)people.size(); ++i) {
            auto p = people[i]; // auto type
            if (p[1] != i) {
                people.erase(people.begin() + i);
                people.insert(people.begin() + p[1], p);
            }
        }
        return people;
    }
};