class Solution {
public:
    Solution(vector<int>& w) {
        // sum[0] = w[0]; // error
        sum = w;
        for (int i = 1; i < w.size(); ++i)
            sum[i] = sum[i - 1] + w[i];
    }
    int pickIndex() {
        // w=[1,3,2], sum=[1,4,6], x=rand()%6=[0,~,5]
        // x=0 -> w1; x=[1,2,3] -> w2; x=[4,5] -> w3
        int x = rand() % sum.back();
        int left = 0, right = sum.size() - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (sum[mid] <= x) left = mid + 1; // error '<', sum is 1-indexed, x is 0-indexed
            else right = mid;
        }
        return left;
    }
private:
    vector<int> sum; // accumulative sum
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */