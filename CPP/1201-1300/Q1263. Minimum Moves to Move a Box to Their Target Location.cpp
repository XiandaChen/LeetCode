class Solution {
public:
    int minPushBox(vector<vector<char>>& grid) {
        int m = grid.size(), n = grid[0].size();
        // state as (box_row, box_col, player_row, player_col)
        bool visited[20][20][20][20]; // 1 <= m, n <= 20
        queue<vector<int>> q; // BFS: queue of state
        int xbox, ybox, xstart, ystart, xtarget, ytarget;
        
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] != '#') {
                    if (grid[i][j] == 'B') {
                        xbox = i; ybox = j;
                    }
                    else if (grid[i][j] == 'S') {
                        xstart = i; ystart = j;
                    }
                    else if (grid[i][j] == 'T') {
                        xtarget = i; ytarget = j;
                    }
                }
            }
        }
        
        q.push({xbox, ybox, xstart, ystart, 0});
        visited[xbox][ybox][xstart][ystart] = true;
        
        while (!q.empty()) {
            vector<int> t = q.front(); q.pop();
            xbox = t[0], ybox = t[1], xstart = t[2], ystart = t[3];
            int steps = t[4];
            
            if (xbox == xtarget && ybox == ytarget) return steps;
            
            // move box ([xbox, ybox]) to right ([xbox+1, ybox])
            // pos [xbox-1, ybox] must be valid for player
            // there is a path from player's pos [xstart, ystart] to [xbox-1, ybox]
            if (xbox + 1 < m && grid[xbox + 1][ybox] != '#'
               && xbox > 0 && grid[xbox - 1][ybox] != '#'
               && !visited[xbox + 1][ybox][xbox][ybox]
               && hasPath(xstart, ystart, xbox - 1, ybox, xbox, ybox, grid)) {
                q.push({xbox + 1, ybox, xbox, ybox, steps + 1});
                visited[xbox + 1][ybox][xbox][ybox] = true;
            }
            
            // move box ([xbox, ybox]) to left ([xbox-1, ybox])
            // pos [xbox+1, ybox] must be valid for player
            // there is a path from player's pos [xstart, ystart] to [xbox+1, ybox]
            if (xbox > 0 && grid[xbox - 1][ybox] != '#'
               && xbox + 1 < m && grid[xbox + 1][ybox] != '#'
               && !visited[xbox - 1][ybox][xbox][ybox]
               && hasPath(xstart, ystart, xbox + 1, ybox, xbox, ybox, grid)) {
                q.push({xbox - 1, ybox, xbox, ybox, steps + 1});
                visited[xbox - 1][ybox][xbox][ybox] = true;
            }
            
            // move box ([xbox, ybox]) to down ([xbox, ybox+1])
            // pos [xbox, ybox-1] must be valid for player
            // there is a path from player's pos [xstart, ystart] to [xbox, ybox-1]
            if (ybox + 1 < n && grid[xbox][ybox + 1] != '#'
               && ybox > 0 && grid[xbox][ybox - 1] != '#'
               && !visited[xbox][ybox+1][xbox][ybox]
               && hasPath(xstart, ystart, xbox, ybox-1, xbox, ybox, grid)) {
                q.push({xbox, ybox + 1, xbox, ybox, steps + 1});
                visited[xbox][ybox + 1][xbox][ybox] = true;
            }
            
            // move box ([xbox, ybox]) to up ([xbox, ybox-1])
            // pos [xbox, ybox+1] must be valid for player
            // there is a path from player's pos [xstart, ystart] to [xbox, ybox+1]
            if (ybox > 0 && grid[xbox][ybox - 1] != '#'
               && ybox + 1 < n && grid[xbox][ybox + 1] != '#'
               && !visited[xbox][ybox-1][xbox][ybox]
               && hasPath(xstart, ystart, xbox, ybox + 1, xbox, ybox, grid)) {
                q.push({xbox, ybox - 1, xbox, ybox, steps + 1});
                visited[xbox][ybox - 1][xbox][ybox] = true;
            }
        }
        
        return -1;
    }
    
    // xstart: player's current pos
    // xpush: the pos player moves to and from there player moves the box
    // xbox: box's current pos
    bool hasPath(int xstart, int ystart, int xpush, int ypush, 
                 int xbox, int ybox, vector<vector<char>>& grid) {
        vector<vector<bool>> memo(20, vector<bool>(20, false));
        return dfs(xstart, ystart, xbox - 1, ybox, xbox, ybox, grid, memo);
    }
    
    bool dfs(int xstart, int ystart, int xpush, int ypush, 
                 int xbox, int ybox, vector<vector<char>>& grid, vector<vector<bool>> & memo) {
        if (grid[xstart][ystart] == '#' || (xstart == xbox && ystart == ybox)) return false;
        
        memo[xstart][ystart] = true;
        
        if (xstart == xpush && ystart == ypush) return true;
            
        bool flag = false;
        int m = grid.size(), n = grid[0].size();
        vector<vector<int>> dirs = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < dirs.size(); i++) {
            if (xstart + dirs[i][0] < 0 || xstart + dirs[i][0] >= m 
                || ystart + dirs[i][1] < 0 || ystart + dirs[i][1] >= n
               || memo[xstart + dirs[i][0]][ystart + dirs[i][1]]) {
                continue;
            }
            else {
                flag = flag || dfs(xstart + dirs[i][0], ystart + dirs[i][1], xpush, ypush, xbox, ybox, grid, memo);
            }
        }
        
        return flag;
    } 
};















