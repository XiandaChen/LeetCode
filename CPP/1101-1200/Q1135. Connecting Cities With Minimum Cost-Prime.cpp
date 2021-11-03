class Solution {
public:
    int minimumCost(int n, vector<vector<int>>& connections) {
        unordered_map<int, vector<pair<int, int>>> graph; // x-<cost, y>
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q; // minHeap:cost
        vector<int> minCost(n + 1, INT_MAX); // Prim's: minCost[v] = min(minCost[v], cost(u,v));
        vector<bool> visited(n + 1, false);
        int numVisited = 0, res = 0;
        
        for (auto & a : connections) {
            graph[a[0]].push_back({a[2], a[1]});
            graph[a[1]].push_back({a[2], a[0]});
        }
        
        q.push({0, 1});  // N: 1 to N
        
        while (numVisited < n && !q.empty()) {
            int cost = q.top().first, city = q.top().second;
            q.pop();
            if (visited[city]) continue;
            visited[city] = true;
            numVisited++;
            res += cost;
            for (auto & a : graph[city]) { // level-order
                cost = a.first; city = a.second;
                if (!visited[city] && cost < minCost[city]) {
                    minCost[city] = cost;
                    q.push({cost, city});
                }
            }
        }
        
        return numVisited == n ? res : -1;
    }
};