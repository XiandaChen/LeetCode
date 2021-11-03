class Solution {
public:
    int getFood(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<vector<int>> q; // <i, j>
        
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == '*') { // starting position
                    q.push({i, j}); 
                    break;
                }
            }
        }
        
        int step = 0;
        while (!q.empty()) {
            step++;
            for (int i = q.size(); i > 0; i--) {
                auto cur = q.front(); q.pop();
                for (auto dir : dirs) {
                    int x = cur[0] + dir[0], y = cur[1] + dir[1];
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] == 'X') continue;
                    if (grid[x][y] == '#') return step; // found the target
                    grid[x][y] = 'X'; // [x][y] has been visited
                    q.push({x, y});
                }
            }
        }
        
        return -1;
    }
};