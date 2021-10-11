class Solution {
public:
    int shortestBridge(vector<vector<int>>& grid) {
        int n = grid.size(), startX = -1, startY = -1, res = 0;
        queue<int> q; // hold 1s, search layer by layer
        
        // find the first non-0 x and y to start the search
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) continue;
                // if (grid[i][j] == 1) {
                    startX = i;
                    startY = j;
                    break;
                // }
            }
            if (startX != -1) break;
        }
        
        // 1. find the first island, all 1's for that island
        helper(grid, startX, startY, q);
        
        // 2. BFS, layer-by-layer to search the island
        int dim[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        while (!q.empty()) {
            for (int i = q.size(); i > 0; i--) {
                int t = q.front(); q.pop();

                for (auto & a : dim) { // search four directions
                    int x = t / n + a[0], y = t % n + a[1];
                    
                    if (x < 0 || x >= n || y < 0 || y >= n || grid[x][y] == 2) continue;
                    
                    if (grid[x][y] == 1) return res; // two islands are connected
                    
                    grid[x][y] = 2;
                    q.push(x * n + y);
                }
            }
            res++;
        }
        
        return res;
    }
    
    void helper(vector<vector<int>> & grid, int x, int y, queue<int> & q) {
        int n = grid.size();
        
        // grid[x][y] == 2: node has been visited
        if (x < 0 || x >= n || y < 0 || y >= n 
            || grid[x][y] == 0 || grid[x][y] == 2) return;
        
        q.push(x * n + y);  // convert 2D idx to 1D idx
        
        grid[x][y] = 2;  // set visited
        
        // traverse four directions
        int dim[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (auto & a : dim) {
            helper(grid, x + a[0], y + a[1], q);
        }
    }
};