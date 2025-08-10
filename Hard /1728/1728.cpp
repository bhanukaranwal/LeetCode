#include <vector>
#include <string>
#include <cstring>

class Solution {
private:
    int rows, cols;
    int catJump, mouseJump;
    int food_r, food_c;
    std::vector<std::string> grid;
    int memo[130][8][8][8][8]; // turn, mr, mc, cr, cc
    const int dirs[5] = {0, 1, 0, -1, 0};

    bool solve(int turn, int mr, int mc, int cr, int cc) {
        if (turn >= 128) return false;
        if (mr == cr && mc == cc) return false;
        if (mr == food_r && mc == food_c) return true;
        if (cr == food_r && cc == food_c) return false;

        if (memo[turn][mr][mc][cr][cc] != -1) {
            return memo[turn][mr][mc][cr][cc];
        }

        if (turn % 2 == 0) { // Mouse's turn
            // Stay
            if (solve(turn + 1, mr, mc, cr, cc)) {
                return memo[turn][mr][mc][cr][cc] = true;
            }
            // Move
            for (int i = 0; i < 4; ++i) {
                for (int j = 1; j <= mouseJump; ++j) {
                    int nmr = mr + dirs[i] * j;
                    int nmc = mc + dirs[i + 1] * j;
                    if (nmr < 0 || nmr >= rows || nmc < 0 || nmc >= cols || grid[nmr][nmc] == '#') {
                        break;
                    }
                    if (solve(turn + 1, nmr, nmc, cr, cc)) {
                        return memo[turn][mr][mc][cr][cc] = true;
                    }
                }
            }
            return memo[turn][mr][mc][cr][cc] = false;
        } else { // Cat's turn
            // Stay
            if (!solve(turn + 1, mr, mc, cr, cc)) {
                return memo[turn][mr][mc][cr][cc] = false;
            }
            // Move
            for (int i = 0; i < 4; ++i) {
                for (int j = 1; j <= catJump; ++j) {
                    int ncr = cr + dirs[i] * j;
                    int ncc = cc + dirs[i + 1] * j;
                    if (ncr < 0 || ncr >= rows || ncc < 0 || ncc >= cols || grid[ncr][ncc] == '#') {
                        break;
                    }
                    if (!solve(turn + 1, mr, mc, ncr, ncc)) {
                        return memo[turn][mr][mc][cr][cc] = false;
                    }
                }
            }
            return memo[turn][mr][mc][cr][cc] = true;
        }
    }

public:
    bool canMouseWin(std::vector<std::string>& grid, int catJump, int mouseJump) {
        this->grid = grid;
        this->rows = grid.size();
        this->cols = grid[0].size();
        this->catJump = catJump;
        this->mouseJump = mouseJump;
        
        int start_mr, start_mc, start_cr, start_cc;
        for (int r = 0; r < rows; ++r) {
            for (int c = 0; c < cols; ++c) {
                if (grid[r][c] == 'M') { start_mr = r; start_mc = c; }
                else if (grid[r][c] == 'C') { start_cr = r; start_cc = c; }
                else if (grid[r][c] == 'F') { food_r = r; food_c = c; }
            }
        }
        
        std::memset(memo, -1, sizeof(memo));
        return solve(0, start_mr, start_mc, start_cr, start_cc);
    }
};
