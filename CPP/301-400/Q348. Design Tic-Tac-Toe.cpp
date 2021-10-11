class TicTacToe {
public:
    TicTacToe(int n) {
        board.resize(n, vector<int>(n, 0));
    }
    
    int move(int row, int col, int player) {
        // 0: empty, 1: player1, 2: player2
        board[row][col] = player;
        
        int n = board.size(), i = 0, j = 0;
        
        // check horizontal
        for (j = 1; j < n; j++) {
            if (board[row][j] != board[row][j - 1]) break;
        }
        if (j == n) return player;
        
        // check vertical
        for (i = 1; i < n; i++) {
            if (board[i][col] != board[i - 1][col]) break;
        }
        if (i == n) return player;
        
        // check diagonal
        if (row == col) { // left diagonal
            for (i = 1; i < n; i++) {
                if (board[i][i] != board[i - 1][i - 1]) break;
            }
            if (i == n) return player;
        }
        // NOTE, not "else if" for case row=col=n/2
        if (row + col == n - 1) { // right diagonal
            for (i = 1; i < n; i++) {
                if (board[n - 1 - i][i] != board[n - i][i - 1]) break;
            }
            if (i == n) return player;
        }
        
        return 0;
    }
private:
    vector<vector<int>> board;
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */