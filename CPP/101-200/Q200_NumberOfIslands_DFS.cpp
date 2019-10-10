class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        vector<vector<bool>> visited(m, vector<bool>(n));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '0' || visited[i][j]) continue;
                numIslands(grid, i, j, visited);
                ++res;
            }
        }
        return res;
    }
    void numIslands(vector<vector<char>> & grid, int i, int j, vector<vector<bool>> & visited) {
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size() || grid[i][j] == '0' || visited[i][j]) return;
        visited[i][j] = true;
        numIslands(grid, i - 1, j, visited);
        numIslands(grid, i + 1, j, visited);
        numIslands(grid, i, j - 1, visited);
        numIslands(grid, i, j + 1, visited);
    }
};