class Solution {
public:
    int snakesAndLadders(vector<vector<int>>& board) {
        int n = board.size(), res = 0;
        vector<int> visited(n * n + 1); // board idx: [1, n^2]
        queue<int> q{{1}}; // BFS, starting from bottom-left
        
        while (!q.empty()) {
            for (int i = q.size(); i > 0; i--) {
                int idx = q.front(); q.pop();
                
                if (idx == n * n) return res; // reach the end
                
                for (int j = 1; j <= 6 && idx + j <= n * n; j++) { // 6-sided die
                    vector<int> pos = getPosition(n, idx + j); // NOTE, idx+j
                    // if pos has ladder or not
                    int next = board[pos[0]][pos[1]] == -1 ? (idx + j) : board[pos[0]][pos[1]];
                    
                    if (visited[next]) continue;
                    
                    visited[next] = true;
                    q.push(next);
                }
            }
            res++;
        }
        
        return -1; 
    }
    
    // from 1 to n^2 in a Boustrophedon style 
    vector<int> getPosition(int n, int idx) { 
        int x = (idx - 1) / n, y = (idx - 1) % n; // board idx: [1, n^2]
        if (x % 2 == 1) { // odd row (e.g., 1th), alternating direction from right
            y = n - 1 - y;
        }
        // NOTE, must after changing y if needed
        x = n - 1 - x; // starting from the bottom left of the board (i.e. board[n - 1][0]) 
        return {x, y};
    }
};