class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        vector<int> res = arr;
        while (k < res.size()) {
            if (abs(x - res.front()) <= abs(res.back() - x))
                // res.erase(res.end()); // error
                res.pop_back();
            else
                res.erase(res.begin());
        }
        return res;
    }
};