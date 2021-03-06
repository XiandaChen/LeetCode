class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int total = 0;
        for (int i= 0;  i < gas.size(); ++i) {
            total += gas[i] - cost[i];
        }
        if (total < 0) return -1;
        
        int sum = 0, start = 0;
        for (int i = 0 ; i < gas.size(); ++i) {
            sum += gas[i] - cost[i];
            if (sum < 0) {
                start = i + 1;
                sum = 0;
            }
        }
        return start;
    }
};