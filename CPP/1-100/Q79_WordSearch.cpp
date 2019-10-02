class Solution {
public:
    bool exist(vector<vector<char>>& board, string word) {
        if (board.empty()) return false;
        int m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n));
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < n; ++j)
                if (existDFS(board, word, 0, i, j, visited)) return true;
        return false;
    }
    bool existDFS(vector<vector<char>>& board, string word, int indx, int i, int j, vector<vector<bool>>& visited) {
        if (indx == word.size()) return true;
        int m = board.size(), n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || board[i][j] != word[indx]) return false;
        visited[i][j] = true;
        bool res = existDFS(board, word,indx + 1, i - 1, j, visited) 
                    || existDFS(board, word, indx + 1, i + 1, j, visited)
                    || existDFS(board, word, indx + 1, i, j - 1, visited)
                    || existDFS(board, word, indx + 1, i, j + 1, visited);
        visited[i][j] = false;
        return res;
    }
};