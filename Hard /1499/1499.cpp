class Solution {
public:
    int findMaxValueOfEquation(vector<vector<int>>& points, int k) {
        // The equation is: yi + yj + |xi - xj|, with xi < xj and |xi - xj| <= k
        // Rearranged as: (yi - xi) + (yj + xj)
        deque<pair<int, int>> dq; // {yi - xi, xi}
        int res = INT_MIN;
        for (auto& p : points) {
            int x = p[0], y = p[1];
            // Remove points out of window (x - xi > k)
            while (!dq.empty() && x - dq.front().second > k)
                dq.pop_front();
            // If deque is not empty, update result
            if (!dq.empty())
                res = max(res, y + x + dq.front().first);
            // Maintain deque in decreasing order of (yi - xi)
            while (!dq.empty() && dq.back().first <= y - x)
                dq.pop_back();
            dq.emplace_back(y - x, x);
        }
        return res;
    }
};
