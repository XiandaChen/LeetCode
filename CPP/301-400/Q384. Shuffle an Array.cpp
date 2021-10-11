class Solution {
public:
    Solution(vector<int>& nums) {
        original = nums;
    }
    
    vector<int> reset() {
        return original;
    }
    
    vector<int> shuffle() {
        vector<int> res = original;
        int n = res.size();
        for (int i = 0; i < n; i++) {
            // int idx = rand() % n;
            int idx = i + rand() % (n - i);
            swap(res[i], res[idx]);
        }
        return res;
    }
private:
    vector<int> original;
};
