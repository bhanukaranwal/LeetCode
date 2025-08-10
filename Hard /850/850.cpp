#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int rectangleArea(vector<vector<int>>& rectangles) {
        const int MOD = 1e9 + 7;
        vector<int> ys;
        for (auto& r : rectangles) {
            ys.push_back(r[1]);
            ys.push_back(r[3]);
        }
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        vector<tuple<int, int, int, int>> events;
        for (auto& r : rectangles) {
            int y1 = lower_bound(ys.begin(), ys.end(), r[1]) - ys.begin();
            int y2 = lower_bound(ys.begin(), ys.end(), r[3]) - ys.begin();
            events.emplace_back(r[0], y1, y2, 1);
            events.emplace_back(r[2], y1, y2, -1);
        }
        sort(events.begin(), events.end());
        vector<int> count(ys.size());
        long long area = 0, prev_x = get<0>(events[0]);
        for (int i = 0; i < events.size(); ++i) {
            int x = get<0>(events[i]);
            long long y_sum = 0;
            for (int j = 0; j + 1 < ys.size(); ++j) {
                if (count[j] > 0) y_sum += ys[j + 1] - ys[j];
            }
            area = (area + y_sum * (x - prev_x)) % MOD;
            int y1 = get<1>(events[i]), y2 = get<2>(events[i]), sig = get<3>(events[i]);
            for (int j = y1; j < y2; ++j) count[j] += sig;
            prev_x = x;
        }
        return area;
    }
};
