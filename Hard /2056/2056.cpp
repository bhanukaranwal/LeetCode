#include <vector>
#include <string>
#include <set>
using namespace std;

class Solution {
public:
    // Directions for rook, bishop, queen
    vector<vector<pair<int,int>>> dirs = {
        {{1,0},{-1,0},{0,1},{0,-1}}, // rook
        {{1,1},{1,-1},{-1,1},{-1,-1}}, // bishop
        {{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}} // queen
    };

    // Get all possible destinations for a piece
    vector<pair<int,int>> getDests(string piece, int r, int c) {
        set<pair<int,int>> s;
        int idx = (piece == "rook") ? 0 : (piece == "bishop") ? 1 : 2;
        s.insert({r, c});
        for (auto d : dirs[idx]) {
            int nr = r, nc = c;
            while (true) {
                nr += d.first;
                nc += d.second;
                if (nr < 1 || nr > 8 || nc < 1 || nc > 8) break;
                s.insert({nr, nc});
            }
        }
        return vector<pair<int,int>>(s.begin(), s.end());
    }

    int countCombinations(vector<string>& pieces, vector<vector<int>>& positions) {
        int n = pieces.size();
        vector<vector<pair<int,int>>> allDests(n);
        for (int i = 0; i < n; ++i) {
            allDests[i] = getDests(pieces[i], positions[i][0], positions[i][1]);
        }

        int res = 0;
        vector<int> idx(n, 0);
        // Try all destination combinations (brute-force, but n <= 4)
        function<void(int)> dfs = [&](int d) {
            if (d == n) {
                // Simulate this move combination
                vector<pair<int,int>> src(n);
                vector<pair<int,int>> dst(n);
                for (int i = 0; i < n; ++i) {
                    src[i] = {positions[i][0], positions[i][1]};
                    dst[i] = allDests[i][idx[i]];
                }
                // For each piece, get movement direction
                vector<pair<int,int>> dir(n);
                vector<int> steps(n);
                int maxStep = 0;
                for (int i = 0; i < n; ++i) {
                    int dr = dst[i].first - src[i].first;
                    int dc = dst[i].second - src[i].second;
                    if (dr != 0) dr /= abs(dr);
                    if (dc != 0) dc /= abs(dc);
                    dir[i] = {dr, dc};
                    steps[i] = max(abs(dst[i].first - src[i].first), abs(dst[i].second - src[i].second));
                    maxStep = max(maxStep, steps[i]);
                }
                // Simulate movement
                vector<pair<int,int>> pos = src;
                set<vector<pair<int,int>>> seen;
                for (int t = 0; t <= maxStep; ++t) {
                    set<pair<int,int>> occ;
                    for (int i = 0; i < n; ++i) {
                        if (t <= steps[i]) {
                            pos[i].first = src[i].first + dir[i].first * min(t, steps[i]);
                            pos[i].second = src[i].second + dir[i].second * min(t, steps[i]);
                        }
                        occ.insert(pos[i]);
                    }
                    if (occ.size() < n) return; // collision
                }
                res++;
                return;
            }
            for (int i = 0; i < allDests[d].size(); ++i) {
                idx[d] = i;
                dfs(d + 1);
            }
        };
        dfs(0);
        return res;
    }
};
