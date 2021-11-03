class Solution {
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        // time: dfs access orders, low: lowest time among all accessable nodes
        vector<int> time(n), low(n); 
        unordered_map<int, vector<int>> graph;
        vector<vector<int>> res;
        int cnt = 1; // dfs access nodes naming cnt from 1
        
        for (auto con : connections) {
            graph[con[0]].push_back(con[1]);
            graph[con[1]].push_back(con[0]);
        }
        
        helper(graph, -1, 0, cnt, time, low, res);
        return res;
    }
    
    void helper(unordered_map<int, vector<int>> & graph, int pre, int cur, int cnt, 
               vector<int> & time, vector<int> & low, vector<vector<int>> & res) {
        time[cur] = low[cur] = cnt++;
        for (int next : graph[cur]) {
            if (time[next] == 0) { // dfs access, and update low[cur]
                helper(graph, cur, next, cnt, time, low, res);
                low[cur] = min(low[cur], low[next]); // NOTE, min(low, low)
            }
            else if (next != pre) { // NOTE, must check (next != pre)
                low[cur] = min(low[cur], time[next]);
            }
            // critical edge
            if (low[next] > time[cur]) res.push_back({cur, next});
        }
    }
};

