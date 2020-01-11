class Solution {
public:
    int hIndex(vector<int>& citations) {
        int n = citations.size();
        // cnt[i]: num of papers that has at least i citations
        vector<int> cnt(n + 1); 
        for (int c : citations) { // increasing order
            if (c <= n) ++cnt[c]; // record, if <= n
            else ++cnt[n]; // for paper whose citations > n, record in [n]
        }
        // traverse from right to left
        int sum = 0;
        for (int i = n; i >= 0; --i) {
            sum += cnt[i];
            if (i <= sum) return i; 
        }
        return 0;
    }
};