class TicTacToe {
public:
    TicTacToe(int n) {
        rows.resize(n);
        cols.resize(n);
        diag = 0;
        rev_diag = 0;
        N = n;
    }
    
    int move(int row, int col, int player) {
        int add = (player == 1) ? 1 : -1;
        
        rows[row] += add;
        cols[col] += add;
        
        diag += (row == col) ? add : 0;  // NOTE, add, not 1
        rev_diag += (row + col == N - 1) ? add: 0;
        
        return (abs(rows[row]) == N || abs(cols[col]) == N
               || abs(diag) == N || abs(rev_diag) == N) ? player : 0;
    }
private:
    // num moves that player1 placed on each row
    // increment 1 if player1 moves on the row
    // derease 1 if player1 moves on that row
    vector<int> rows, cols; 
    
    // num moves that player1 placed on diagonal and reverse diagonal
    int diag, rev_diag, N;
};

/**
 * Your TicTacToe object will be instantiated and called as such:
 * TicTacToe* obj = new TicTacToe(n);
 * int param_1 = obj->move(row,col,player);
 */