#include <vector>
#include <string> // Not strictly needed for char array, but useful for general string ops

class Solution {
public:
    // These boolean arrays will keep track of used digits in rows, columns, and 3x3 boxes.
    // rowUsed[r][digit_idx] is true if digit (digit_idx+1) is used in row 'r'.
    bool rowUsed[9][10]; // Digits 1-9, so index 0 unused, 1-9 maps to digit value
    bool colUsed[9][10];
    // boxUsed[box_row_idx][box_col_idx][digit_idx]
    // box_row_idx = r / 3, box_col_idx = c / 3
    bool boxUsed[3][3][10];

    void solveSudoku(std::vector<std::vector<char>>& board) {
        // Initialize all 'used' arrays to false
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 10; ++j) {
                rowUsed[i][j] = false;
                colUsed[i][j] = false;
            }
        }
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                for (int k = 0; k < 10; ++k) {
                    boxUsed[i][j][k] = false;
                }
            }
        }

        // Pre-populate the 'used' arrays based on the initial board
        for (int r = 0; r < 9; ++r) {
            for (int c = 0; c < 9; ++c) {
                if (board[r][c] != '.') {
                    int digit = board[r][c] - '0'; // Convert char to int
                    rowUsed[r][digit] = true;
                    colUsed[c][digit] = true;
                    boxUsed[r / 3][c / 3][digit] = true;
                }
            }
        }

        // Start the backtracking process
        solve(board, 0, 0); // Start from cell (0,0)
    }

    // Backtracking helper function
    // board: The Sudoku board (modified in place)
    // row, col: Current cell coordinates being considered
    bool solve(std::vector<std::vector<char>>& board, int row, int col) {
        // Move to the next row if current column exceeds 8
        if (col == 9) {
            row++;
            col = 0;
        }

        // Base case: If all rows are processed, a solution has been found
        if (row == 9) {
            return true;
        }

        // If the current cell is not empty, move to the next cell
        if (board[row][col] != '.') {
            return solve(board, row, col + 1);
        }

        // If the current cell is empty ('.')
        for (int digit = 1; digit <= 9; ++digit) {
            // Check if placing 'digit' at (row, col) is valid
            if (!rowUsed[row][digit] && !colUsed[col][digit] && !boxUsed[row / 3][col / 3][digit]) {
                // Choose: Place the digit and mark it as used
                board[row][col] = (char)(digit + '0'); // Convert int to char
                rowUsed[row][digit] = true;
                colUsed[col][digit] = true;
                boxUsed[row / 3][col / 3][digit] = true;

                // Explore: Recurse for the next cell
                if (solve(board, row, col + 1)) {
                    return true; // If a solution is found down this path, propagate true
                }

                // Unchoose (Backtrack): If the recursive call didn't find a solution,
                // undo the choice and mark the digit as unused.
                board[row][col] = '.';
                rowUsed[row][digit] = false;
                colUsed[col][digit] = false;
                boxUsed[row / 3][col / 3][digit] = false;
            }
        }

        // If no digit from 1-9 works for the current empty cell,
        // this path does not lead to a solution.
        return false;
    }
};
