class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        auto cmp = [](vector<int> &a, vector<int> &b) {
            return a[1] < b[1] || (a[1] == b[1] && a[0] < b[0]);    
        };
        sort(events.begin(), events.end(), cmp); // sort inscending by end time
        
        int res = 0, n = events.size();
        vector<bool> attend(events[n - 1][1] + 1, false); 
        int prev = 0;
        for (int i = 0; i < n; ++i) {
        // can attend the event at any dey within [start, end] day
            int start = events[i][0], end = events[i][1];
            if (i > 0 && events[i][0] == events[i - 1][0]) start = prev;
            for (int j = start; j <= end; ++j) {
                if (attend[j]) continue; // already attend other event at day_i 
                attend[j] = true;
                ++res; 
                prev = j;
                break;  // attend this event at day_i
            }
        }
        return res;
    }
};
