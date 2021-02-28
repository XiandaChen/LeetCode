class Solution {
public:
    int countClouds(vector<vector<char>>& grid) {
        if (grid.empty()) return 0;
        int m = grid.size(), n = grid[0].size(), res = 0;
        vector<vector<bool>> visited(m, vector<bool> (n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '0' || visited[i][j]) continue;
                ++res;
                helper(grid, visited, i, j);
            }
        }
        return res;
    }
    void helper(vector<vector<char>>& grid, vector<vector<bool>>& visited, int i, int j) {
        if (i < 0 || i >= grid.size() ||
           j < 0 || j >= grid[0].size() ||
           grid[i][j] == '0' || visited[i][j]) return;
        visited[i][j] = true;
        helper(grid, visited, i + 1, j);
        helper(grid, visited, i - 1, j);
        helper(grid, visited, i, j + 1);
        helper(grid, visited, i, j - 1);
    }
};