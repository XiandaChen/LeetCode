class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size(), res = 0;
        long sum1 = 0, sum2 = 0; // NOTE, long
        
        vector<int> expect = arr;
        sort(expect.begin(), expect.end());
        
        for (int i = 0; i < n; i++) {
            sum1 += arr[i];
            sum2 += expect[i];
            if (sum1 == sum2) res++;
        }
        
        return res;
    }
};