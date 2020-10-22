class Solution {
public:
    vector<double> medianSlidingWindow(vector<int>& nums, int k) {
        vector<double> res;
        multiset<int> small, large; // ascending sort
        for (int i = 0; i < (int)nums.size(); ++i) {
            // remove nums[i-k]
            if (i >= k) {
                if (small.count(nums[i - k])) 
                    small.erase(small.find(nums[i - k]));
                else
                    large.erase(large.find(nums[i - k]));
            }
            // insert nums[i]
            if (small.empty() || *small.rbegin() >= nums[i])
                small.insert(nums[i]);
            else
                large.insert(nums[i]);
            // balance
            if (small.size() > large.size() + 1) {
                large.insert(*small.rbegin());
                // small.erase(small.rbegin()); // error
                small.erase(--small.end());
            }
            else if (small.size() < large.size()) {
                small.insert(*large.begin());
                large.erase(large.begin());
            }
            // find median
            if (i >= k - 1) {
                if (small.size() > large.size())
                    res.push_back(*small.rbegin());
                else // ==
                    res.push_back(((double)*small.rbegin() + *large.begin()) / 2.0);
            }
        }
        return res;
    }
};