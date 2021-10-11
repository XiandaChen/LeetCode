class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        int n = arr.size(), res = 0;
        
        for (int i = 0; i < n; i++) {
            int curMax = arr[i], j = i + 1;
            for (; j <= curMax; j++) {
                curMax = max(curMax, arr[j]); // update the farest reachable pos
                if (curMax >= arr.back()) return res + 1; 
            }
            
            i = j - 1; // NOTE - 1
            res++;
        }
        
        return res;
    }
};