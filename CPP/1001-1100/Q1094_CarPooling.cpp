

class Solution {
public:
    // method 1:
    // struct endCmp {
    //     bool operator()(vector<int> &a, vector<int> &b) {
    //         return a[2] > b[2];  // descending in endtime: min queue
    //     }
    // };
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        auto startCmp = [](vector<int> &a, vector<int> &b) {
           return a[1] < b[1] || (a[1] == b[1] && a[2] < b[2]); 
        };
        sort(trips.begin(), trips.end(), startCmp);
        
        // method 1:
        // priority_queue<vector<int>, vector<vector<int>>, endCmp> q;
        
        // method 2:
        auto endCmp = [](vector<int> &a, vector<int> &b) {
            return a[2] > b[2];  // descending in endtime: min queue
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(endCmp)> q(endCmp); //q(endCmp)
        
        
        int curload = 0, maxload = 0;
        for (auto trip : trips) {
            // remove all trips that have droped off
            while (!q.empty() && q.top()[2] <= trip[1]) {
                curload -= q.top()[0];
                q.pop();
            }
            
            // add cur trip (passengers) onto vehicle
            q.push(trip);
            curload += trip[0];
            maxload = max(maxload, curload);
            
            // check if overloading
            if (maxload > capacity) return false;
        }
        
        return true;
    }
};