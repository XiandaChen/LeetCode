class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int res = 0, m = grid.size(), n = grid[0].size(), freshCnt = 0;
        queue<pair<int, int>> q; // bfs: row-col
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) freshCnt++;
                else if (grid[i][j] == 2) q.push({i, j}); // rotten orange
            }
        }
        
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        while (!q.empty() && freshCnt > 0) { // NOTE, freshCnt > 0
            for (int i = q.size(); i > 0; i--) {
                auto a = q.front(); q.pop();
                for (int k = 0; k < 4; k++) {
                    int row = a.first + dirs[k][0], col = a.second + dirs[k][1];
                    if (row >= 0 && row < m && col >= 0 && col < n
                       && grid[row][col] == 1) {
                        freshCnt--;
                        grid[row][col] = 2;
                        q.push({row, col});
                    }
                }
            }
            res += 1;
        }
        
        return freshCnt == 0 ? res : -1;
    }
};