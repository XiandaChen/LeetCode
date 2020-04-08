// Given an integer array arr, count element x such that x + 1 is also in arr.
// 1,1,1,2,2,4,5,5,6 => 4
class Solution {
public:
    int countElements(vector<int>& arr) { 
        // 1,1,1,2,2,4,5,5,6 => 4
        if (arr.size() < 2) return 0;
        int res = 0;
        sort(arr.begin(), arr.end());
        int i = 0, j = 1;
        while (j < arr.size()) {
            if (arr[i] == arr[j]) ++j; // same, move j forward
            else if (arr[i] + 1 == arr[j]) { // count
                res += 1;
                ++i;
            }
            else { // arr[i]!=arr[j], move i forward
                ++i;
            }
        }
        return res;
    }
};