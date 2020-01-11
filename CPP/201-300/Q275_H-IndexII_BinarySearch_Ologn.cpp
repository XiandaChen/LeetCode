class Solution {
public:
    int hIndex(vector<int>& citations) {
        int len = citations.size(); 
        if (len == 0 || citations[len - 1] <= 0) return 0;
        int left = 0, right = len - 1;
        while (left < right) {
            int mid = left + (right - left) / 2;
            // citations in increasing order, [0,1,3,5,6], check from right 
            // num of citations of (len-mid)-th paper is less than (len-mid)  
            if (citations[mid] < len - mid) 
                left = mid + 1;
            else // (len-mid)-th paper has at least (len-mid) citations
                right = mid;
        }
        return len - right;
    }
};