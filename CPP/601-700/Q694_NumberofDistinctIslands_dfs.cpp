class Solution {
public:
    int numDistinctIslands(vector<vector<int>>& grid) {
        if (grid.empty()) return 0;
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        unordered_set<string> islands; // island patterns
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (grid[i][j] == 1 && !visited[i][j]) {
                    set<string> nodes;
                    dfs(grid, visited, i, j, i, j, nodes);
                    string island = "";
                    for (auto n : nodes) { // encoding the island
                        island += n + "_";
                    }
                    islands.insert(island);
                }
            }
        }
        return islands.size();
    }
    void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, 
             int x0, int y0, int i, int j, set<string>& nodes) {
        if (i < 0 || i >= grid.size()
           || j < 0 || j >= grid[0].size()
           || grid[i][j] == 0 || visited[i][j]) return;
        
        visited[i][j] = true;
        nodes.insert(to_string(i - x0) + "_" + to_string(j - y0)); // relative dist to upleft node
        
        dfs(grid, visited, x0, y0, i + 1, j, nodes);
        dfs(grid, visited, x0, y0, i - 1, j, nodes);
        dfs(grid, visited, x0, y0, i, j + 1, nodes);
        dfs(grid, visited, x0, y0, i, j - 1, nodes);
    }
};
