class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty()) return false;
        int m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (existDFS(board, word, 0, i, j)) return true;
        return false;
    }
    bool existDFS(vector<vector<char>>& board, string word, int indx, int i, int j) {
        if (indx == word.size()) return true;
        int m = board.size(), n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || board[i][j] != word[indx]) return false;
        char ch = board[i][j];
        board[i][j] = '#';
        bool res = existDFS(board, word,indx + 1, i - 1, j) 
                    || existDFS(board, word, indx + 1, i + 1, j)
                    || existDFS(board, word, indx + 1, i, j - 1)
                    || existDFS(board, word, indx + 1, i, j + 1);
        board[i][j] = ch;
        return res;
    }
};