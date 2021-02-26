// A soduku is valid if only if: 
// Each row/column/3x3-sub-boxes must contain the digits 1-9 without repetition.
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<string> st;
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') continue;
                // encode the status of number occurrance
                string num = "(" + to_string(board[i][j]) + ")";
                string row = to_string(i) + num, col = num + to_string(j);
                string cell = to_string(i / 3) + num + to_string(j / 3);  // i/3, j/3
                if (st.count(row) || st.count(col) || st.count(cell)) return false;
                st.insert(row);
                st.insert(col);
                st.insert(cell);
            }
        }
        return true;
    }
};