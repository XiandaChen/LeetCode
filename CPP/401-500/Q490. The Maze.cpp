class Solution {
public:
    vector<vector<int>> dirs = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
    
    bool hasPath(vector<vector<int>>& maze, vector<int>& start, vector<int>& destination) {
        return helper(maze, start[0], start[1], destination[0], destination[1]);
    }
    
    bool helper(vector<vector<int>>& maze, int i, int j, int di, int dj) {
        if (i == di && j == dj) return true; // reach the destination
        maze[i][j] = -1; // memoization, [i][j] has been visited
        
        int m = maze.size(), n = maze[0].size();
        bool res = false;
        
        for (auto dir : dirs) {
            int x = i, y = j;
            while (x >= 0 && x < m && y >= 0 && y < n && maze[x][y] != 1) {
                x += dir[0]; y += dir[1]; // keep going until reaching wall
            }
            x -= dir[0]; y -= dir[1];  // trace back to previous empty space
            
            if (maze[x][y] != -1) { //[x][y] is empty space and have not been visited yet
                res |= helper(maze, x, y, di, dj); // dfs
            }
        }
        
        return res;
    }
};