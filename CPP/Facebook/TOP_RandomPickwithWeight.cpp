class Solution {
public:
    Solution(vector<int>& w) {
        sum = w;
        for (int i = 1; i < w.size(); ++i)
            sum[i] = sum[i - 1] + w[i];
    }
    int pickIndex() {
        // w=[1,3,2], sum=[1,4,6], x=rand()%6=[0,~,5]
        // x=0 -> w1; x=[1,2,3] -> w2; x=[4,5] -> w3
        int x = rand() % sum.back();
        int left = 0, right = sum.size() - 1;
        while (left < right) { // firstGreater
            int mid = left + (right - left) / 2;
            if (sum[mid] <= x) left = mid + 1;
            else right = mid;        }
        return right;    }
private:
    vector<int> sum; // accumulative sum
};