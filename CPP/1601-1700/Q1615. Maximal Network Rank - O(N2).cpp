class Solution {
public:
    int maximalNetworkRank(int n, vector<vector<int>>& roads) {
        unordered_map<int, set<int>> graph; // node-connectedNodes
        
        int res = 0;
        
        for (auto & road : roads) {
            graph[road[0]].insert(road[1]);
            graph[road[1]].insert(road[0]);            
        }
        
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (!graph[i].count(j)) { // i, j are seperate
                    res = max(res, int(graph[i].size() + graph[j].size()));
                }
                else { // nodes i and j are connected
                    res = max(res, int(graph[i].size() + graph[j].size() - 1));
                }
            }
        }
        
        return res;
    }
};