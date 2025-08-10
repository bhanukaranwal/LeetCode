#include <vector>
#include <numeric>
#include <algorithm>

class Solution {
private:
    std::vector<std::vector<int>> memo;
    std::vector<int> prefixSum;

    // solve(i, j) returns the max score Alice can get from the range [i, j].
    int solve(int i, int j) {
        // Base case: a single stone means the game ends, no score from this subproblem.
        if (i == j) {
            return 0;
        }
        // Return the cached result if we've already solved this subproblem.
        if (memo[i][j] != -1) {
            return memo[i][j];
        }

        int max_score = 0;

        // Alice tries every possible split point 'k'.
        for (int k = i; k < j; ++k) {
            // Calculate sums of the two new rows using our prefixSum array.
            int left_sum = prefixSum[k + 1] - prefixSum[i];
            int right_sum = prefixSum[j + 1] - prefixSum[k + 1];
            
            int current_round_score = 0;
            if (left_sum > right_sum) {
                // Bob throws away the left row; game continues on the right.
                current_round_score = right_sum + solve(k + 1, j);
            } else if (right_sum > left_sum) {
                // Bob throws away the right row; game continues on the left.
                current_round_score = left_sum + solve(i, k);
            } else { 
                // Sums are equal; Alice chooses the better outcome.
                current_round_score = left_sum + std::max(solve(i, k), solve(k + 1, j));
            }
            
            // Alice wants the split 'k' that maximizes her total score.
            max_score = std::max(max_score, current_round_score);
        }

        // Cache the result and return it.
        return memo[i][j] = max_score;
    }

public:
    int stoneGameV(std::vector<int>& stoneValue) {
        int n = stoneValue.size();
        if (n <= 1) {
            return 0;
        }

        memo.assign(n, std::vector<int>(n, -1));

        // Pre-calculate prefix sums for O(1) range sum queries.
        prefixSum.assign(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + stoneValue[i];
        }

        return solve(0, n - 1);
    }
};
