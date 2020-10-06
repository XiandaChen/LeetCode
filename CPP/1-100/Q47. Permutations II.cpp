class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> res(1); // initial with one empty subset
        for (int num : nums) {
            for (int i = res.size(); i > 0; --i) {
                vector<int> tmp = res.front();
                res.erase(res.begin());
                for (int j = 0; j <= tmp.size(); ++j) { // <=: [1,2]==>[3,1,2],[1,3,2],[1,2,3]
                    vector<int> newone(tmp);
                    newone.insert(newone.begin() + j, num);
                    res.push_back(newone);
                    // trim duplicate ones
                    if (j < tmp.size() && num == tmp[j]) break;
                }
            }
        }
        return res;
    }
};