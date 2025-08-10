class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        vector<int> cols(n);
        vector<string> board(n, string(n, '.'));
        backtrack(0, n, cols, board, result);
        return result;
    }
private:
    void backtrack(int row, int n, vector<int>& cols, vector<string>& board, vector<vector<string>>& result) {
        if (row == n) {
            result.push_back(board);
            return;
        }
        for (int col = 0; col < n; col++) {
            if (isSafe(row, col, cols)) {
                cols[row] = col;
                board[row][col] = 'Q';
                backtrack(row + 1, n, cols, board, result);
                board[row][col] = '.';
            }
        }
    }
    bool isSafe(int row, int col, vector<int>& cols) {
        for (int prevRow = 0; prevRow < row; prevRow++) {
            int prevCol = cols[prevRow];
            if (prevCol == col || abs(prevRow - row) == abs(prevCol - col)) {
                return false;
            }
        }
        return true;
    }
};
