class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end(), [](vector<int> &a, vector<int> &b) {
           return a[1] < b[1]; // sort increasing by end time 
        });
        
        int res = 0;
        vector<bool> attend(100001, false); // events.length <= 10^5
        
        for (auto e : events) {
            for (int i = e[0]; i <= e[1]; ++i) {
                if (attend[i]) continue; // if day i had been for other events
                attend[i] = true;
                ++res;
                break; // must, event e can be attended at day i
            }
        }
        
        return res;
    }
};