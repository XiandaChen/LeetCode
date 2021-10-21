class Solution {
public:
    int longestLine(vector<vector<int>>& mat) {
        if (mat.empty()) return 0;
        
        int m = mat.size(), n = mat[0].size(), res = 0;
        
        // horizontal
        for (int i = 0; i < m; i++) { 
            int cnt = 0;
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // vertical
        for (int j = 0; j < n; j++) { 
            int cnt = 0;
            for (int i = 0; i < m; i++) {
                if (mat[i][j] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // upper diagonal, starting from [x=0][y=j], then x++,y++
        for (int j = 0; j < n; j++) {
            int cnt = 0;
            for (int x = 0, y = j; x < m && y < n; x++, y++) {
                if (mat[x][y] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // lower diagonal, starting from [x=1][y=0], then x++,y++
        for (int i = 1; i < m; i++) {
            int cnt = 0;
            for (int x = i, y = 0; x < m && y < n; x++, y++) {
                if (mat[x][y] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // upper anti-diagonal, starting from [x=0][y=n-j-1], then x++,y--
        for (int j = 0; j < n; j++) {
            int cnt = 0;
            for (int x = 0, y = n - j - 1; x < m && y >= 0; x++, y--) {
                if (mat[x][y] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        // lower anti-diagonal, starting from [x=i][y=n-1], then x++,y--
        for (int i = 1; i < m; i++) {
            int cnt = 0;
            for (int x = i, y = n - 1; x < m && y >= 0; x++, y--) {
                if (mat[x][y] == 1) res = max(res, ++cnt);
                else cnt = 0;
            }
        }
        
        return res;
    }
};





