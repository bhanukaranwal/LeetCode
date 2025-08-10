#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        int n = rooms.size(), q = queries.size();
        // Sort rooms by size descending
        sort(rooms.begin(), rooms.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] > b[1];
        });
        // Store queries with their original indices, sort by minSize descending
        vector<tuple<int, int, int>> qs; // {minSize, preferred, idx}
        for (int i = 0; i < q; ++i)
            qs.emplace_back(queries[i][1], queries[i][0], i);
        sort(qs.rbegin(), qs.rend()); // sort by minSize descending

        set<int> ids; // room ids with size >= minSize
        vector<int> res(q, -1);
        int i = 0;
        for (auto& [minSize, preferred, idx] : qs) {
            // Add all rooms with size >= minSize to the set
            while (i < n && rooms[i][1] >= minSize) {
                ids.insert(rooms[i][0]);
                ++i;
            }
            if (ids.empty()) continue;
            // Find closest id to preferred
            auto it = ids.lower_bound(preferred);
            int ans = -1, diff = INT_MAX;
            if (it != ids.end()) {
                if (abs(*it - preferred) < diff || (abs(*it - preferred) == diff && *it < ans)) {
                    ans = *it;
                    diff = abs(*it - preferred);
                }
            }
            if (it != ids.begin()) {
                --it;
                if (abs(*it - preferred) < diff || (abs(*it - preferred) == diff && *it < ans)) {
                    ans = *it;
                    diff = abs(*it - preferred);
                }
            }
            res[idx] = ans;
        }
        return res;
    }
};
