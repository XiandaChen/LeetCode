class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), res = 0;
        bool hasZero = false;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) continue;
                
                hasZero =  true;
                
                grid[i][j] = 1; // change 0 to 1, then search num ones starting from [i][j]
                vector<vector<bool>> visited(m, vector<bool>(n, false));
                res = max(res, helper(grid, i, j, visited));
                if (res == m * n) return res; // NOTE
                grid[i][j] = 0; // reset [i][j]
            }
        }
        
        return (hasZero) ? res : m * n;
    }
    
    int helper(vector<vector<int>>& grid, int i, int j, vector<vector<bool>> & visited) {
        int m = grid.size(), n = grid[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || grid[i][j] == 0 || visited[i][j]) return 0;
        
        visited[i][j] = true;
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int res = 1;  // 1 for current [i][j]
        for (auto & dir : dirs) {
            res += helper(grid, i + dir[0], j + dir[1], visited);
        }
        return res;
    }
};
