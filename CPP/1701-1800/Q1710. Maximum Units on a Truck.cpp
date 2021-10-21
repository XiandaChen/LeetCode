class Solution {
public:
    int maximumUnits(vector<vector<int>>& boxTypes, int truckSize) {
        auto cmp = [](vector<int> &a, vector<int> &b) {
            return a[1] > b[1]; // descending
        };
        sort(boxTypes.begin(), boxTypes.end(), cmp); // sort descending by unit
        
        int res = 0, n = boxTypes.size();
        for (int i = 0; i < n; i++) {
            int boxs = boxTypes[i][0], unit = boxTypes[i][1];
            
            while (truckSize > 0 && boxs > 0) {
                res += unit;
                boxs--;
                truckSize--;
                if (boxs <= 0 || truckSize <= 0) break;
            }
            
            if (truckSize <= 0) return res;
            
        }
        return res;
    }
};