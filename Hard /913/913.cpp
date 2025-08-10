#include <vector>
#include <queue>

class Solution {
public:
    int catMouseGame(std::vector<std::vector<int>>& graph) {
        int n = graph.size();
        
        // State: dp[mouse_pos][cat_pos][turn]
        // turn 0: mouse's turn, turn 1: cat's turn
        // outcome 0: undecided/draw, 1: mouse wins, 2: cat wins
        std::vector<std::vector<std::vector<int>>> dp(n, std::vector<std::vector<int>>(n, std::vector<int>(2, 0)));
        
        // out_degree[mouse_pos][cat_pos][turn] = number of available moves from this state
        std::vector<std::vector<std::vector<int>>> out_degree(n, std::vector<std::vector<int>>(n, std::vector<int>(2, 0)));

        for (int m = 0; m < n; ++m) {
            for (int c = 1; c < n; ++c) {
                out_degree[m][c][0] = graph[m].size();
                out_degree[m][c][1] = graph[c].size();
                // Cat cannot move to the hole (node 0)
                for (int neighbor : graph[c]) {
                    if (neighbor == 0) {
                        out_degree[m][c][1]--;
                        break;
                    }
                }
            }
        }
        
        // Use a queue for a BFS-style coloring of states
        std::queue<std::vector<int>> q;
        
        // Initialize terminal states
        for (int c = 1; c < n; ++c) {
            // Mouse reaches the hole (node 0)
            dp[0][c][0] = 1;
            dp[0][c][1] = 1;
            q.push({0, c, 0});
            q.push({0, c, 1});
        }
        for (int m = 1; m < n; ++m) {
            // Cat catches the mouse
            dp[m][m][0] = 2;
            dp[m][m][1] = 2;
            q.push({m, m, 0});
            q.push({m, m, 1});
        }

        // Propagate results from terminal states backwards
        while (!q.empty()) {
            std::vector<int> state = q.front();
            q.pop();
            int m_pos = state[0], c_pos = state[1], turn = state[2];
            int outcome = dp[m_pos][c_pos][turn];
            
            // Find all parent states that could have led to this one
            int prev_turn = 1 - turn;
            
            if (prev_turn == 0) { // Previous turn was Mouse's
                // The previous state was (prev_m_pos, c_pos, 0)
                for (int prev_m_pos : graph[m_pos]) {
                    if (dp[prev_m_pos][c_pos][0] == 0) { // If parent state is still undecided
                        if (outcome == 1) { // Mouse found a winning move
                            dp[prev_m_pos][c_pos][0] = 1;
                            q.push({prev_m_pos, c_pos, 0});
                        } else { // Mouse found a losing move (outcome == 2)
                            out_degree[prev_m_pos][c_pos][0]--;
                            if (out_degree[prev_m_pos][c_pos][0] == 0) {
                                dp[prev_m_pos][c_pos][0] = 2;
                                q.push({prev_m_pos, c_pos, 0});
                            }
                        }
                    }
                }
            } else { // Previous turn was Cat's
                // The previous state was (m_pos, prev_c_pos, 1)
                for (int prev_c_pos : graph[c_pos]) {
                    if (prev_c_pos == 0) continue;
                    if (dp[m_pos][prev_c_pos][1] == 0) { // If parent state is still undecided
                        if (outcome == 2) { // Cat found a winning move
                            dp[m_pos][prev_c_pos][1] = 2;
                            q.push({m_pos, prev_c_pos, 1});
                        } else { // Cat found a losing move (outcome == 1)
                             out_degree[m_pos][prev_c_pos][1]--;
                            if (out_degree[m_pos][prev_c_pos][1] == 0) {
                                dp[m_pos][prev_c_pos][1] = 1;
                                q.push({m_pos, prev_c_pos, 1});
                            }
                        }
                    }
                }
            }
        }
        
        // Return the outcome for the starting state of the game
        return dp[1][2][0];
    }
};
