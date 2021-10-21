class Solution {
public:
    int shortestDistance(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size(), buildingCnt = 0, res = INT_MAX;
        // dist[x][y]: accumulated dist from buildings to pos[x][y],
        // cnt[x][y]: num buildings that have counted at pos[x][y]
        vector<vector<int>> dist(m, vector<int>(n,0)), cnt = dist;
        vector<vector<int>> dirs = {{-1 ,0}, {0, 1}, {1, 0}, {0, -1}};
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) { // updte dist from a building
                    buildingCnt++;
                    queue<pair<int, int>> q; // level-order search
                    q.push({i, j});
                    vector<vector<bool>> visited(m, vector<bool>(n, false));
                    int level = 1;
                    
                    while (!q.empty()) {
                        for (int s = q.size(); s > 0; s--) {
                            int x0 = q.front().first, y0 = q.front().second;
                            q.pop();
                            
                            for (int k = 0; k < dirs.size(); k++) {
                                int x = x0 + dirs[k][0], y = y0 + dirs[k][1];
                                if (x >= 0 && x < m && y >= 0 && y < n && grid[x][y] == 0 && !visited[x][y]) {
                                    dist[x][y] += level;
                                    cnt[x][y]++;
                                    visited[x][y] = true;
                                    q.push({x, y});
                                }
                            }
                        }
                        level++; // NOTE
                    }
                }
            }
        }
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                // [i][j] is empty land and can reach all buildings
                if (grid[i][j] == 0 && cnt[i][j] == buildingCnt)
                    res = min(res, dist[i][j]);
            }
        }
        
        return res == INT_MAX ? -1 : res;
    }
};

