#include <vector>
#include <cmath>

class Solution {
public:
    bool winnerSquareGame(int n) {
        // dp[i] will be true if starting with 'i' stones is a winning position.
        std::vector<bool> dp(n + 1, false);

        // Iterate from 1 up to n to fill the dp table.
        for (int i = 1; i <= n; ++i) {
            // Check every possible move from state 'i'.
            // A move is subtracting a square number j*j.
            for (int j = 1; j * j <= i; ++j) {
                // If we can make a move to a state (i - j*j) that is a
                // losing position for the opponent (!dp[...]), then the current
                // state 'i' is a winning position for us.
                if (!dp[i - j * j]) {
                    dp[i] = true;
                    // We found a winning move, so we can stop checking other
                    // moves for this 'i' and move to the next number.
                    break;
                }
            }
        }

        // The answer is whether the starting position 'n' is a winning one.
        return dp[n];
    }
};
