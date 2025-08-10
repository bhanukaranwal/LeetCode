#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = queries.size();
        vector<pair<int, int>> qs;
        for (int i = 0; i < n; ++i) qs.push_back({queries[i], i});
        sort(qs.begin(), qs.end());
        sort(intervals.begin(), intervals.end());
        vector<int> res(n, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        int j = 0;
        for (auto& q : qs) {
            int val = q.first, idx = q.second;
            while (j < intervals.size() && intervals[j][0] <= val) {
                int l = intervals[j][0], r = intervals[j][1];
                pq.push({r - l + 1, r});
                ++j;
            }
            while (!pq.empty() && pq.top().second < val) pq.pop();
            if (!pq.empty()) res[idx] = pq.top().first;
        }
        return res;
    }
};
