class Solution {
public:
    void solveSudoku(vector<vector<char>>& board) {
        helper(board, 0, 0);
    }
    bool helper(vector<vector<char>> & board, int i, int j) {
        if (i == 9) return true; // successfully check all rows
        if (j >= 9) return helper(board, i + 1, 0); // check new row
        if (board[i][j] != '.') return helper(board, i, j + 1); // not need to feel position[i][j]
        
        for (char c = '1'; c <= '9'; c++) {
            if (!isValid(board, i, j, c)) continue; // char c not fit
            board[i][j] = c;
            
            if (helper(board, i, j + 1)) return true; // 
            board[i][j] = '.'; // else, reset pos[i][j] to '.'
        }
        
        return false;
    }
    bool isValid(vector<vector<char>> & board, int i, int j, char val) {
        for (int x = 0; x < 9; x++) {
            if (board[x][j] == val) return false;
        }
        for (int y = 0; y < 9; y++) {
            if (board[i][y] == val) return false;
        }
        
        // 9 3x3 subboxes have exactly 1-9 once
        int row = i - i % 3, col = j - j % 3;
        for (int x = 0; x < 3; x++) {
            for (int y = 0; y < 3; y++) {
                if (board[row + x][col + y] == val) return false;
            }
        }
        
        return true;
    }
};