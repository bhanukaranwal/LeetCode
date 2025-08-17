#include <vector>
using namespace std;

class Solution {
public:
    vector<int> parent;

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        parent[find(x)] = find(y);
    }

    vector<bool> friendRequests(int n, vector<vector<int>>& restrictions, vector<vector<int>>& requests) {
        parent.resize(n);
        for (int i = 0; i < n; ++i) parent[i] = i;
        vector<bool> res;

        for (auto& req : requests) {
            int u = req[0], v = req[1];
            int pu = find(u), pv = find(v);
            bool valid = true;
            if (pu != pv) {
                // Check all restrictions
                for (auto& r : restrictions) {
                    int x = r[0], y = r[1];
                    int px = find(x), py = find(y);
                    // If x and u would be in the same set, and y and v would be in the same set, then merging u and v would violate restriction
                    if ((pu == px && pv == py) || (pu == py && pv == px)) {
                        valid = false;
                        break;
                    }
                }
            }
            if (valid) {
                res.push_back(true);
                if (pu != pv) unite(pu, pv);
            } else {
                res.push_back(false);
            }
        }
        return res;
    }
};
