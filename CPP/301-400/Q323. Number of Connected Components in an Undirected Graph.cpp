class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n);
        vector<bool> visited(n, false);
        int res = 0;
        
        // adjacent list
        for (auto & a: edges) {
            graph[a[0]].push_back(a[1]);
            graph[a[1]].push_back(a[0]);
        }
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                res++;
                dfs(graph, visited, i);
            }
        }
        
        return res;
    }
    
    void dfs(vector<vector<int>> & graph, vector<bool> & visited, int i) {
        if (visited[i]) return;
        visited[i] = true;
        for (auto & a: graph[i])
            dfs(graph, visited, a);
    }
};