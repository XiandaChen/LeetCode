class Solution {
public:
    int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
        int cur = startFuel, stops = 0, i = 0;
        priority_queue<int> q; // gas (high to low) of reachable stations
        while (true) {
            if (cur >= target) return stops; // currently reachable distance >= target
            while (i < stations.size() && stations[i][0] <= cur)
                q.push(stations[i++][1]); // max heap: all reachable stations
            if (q.empty()) break; // cur dist not reach target, and no stations available
            cur += q.top(); // fuel at the station with highest gas
            q.pop();
            ++stops;
        }
        return -1;
    }
};