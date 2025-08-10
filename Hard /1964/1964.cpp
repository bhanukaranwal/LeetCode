class Solution {
public:
    vector<int> longestObstacleCourseAtEachPosition(vector<int>& obstacles) {
        int n = obstacles.size();
        vector<int> ans(n);
        vector<int> piles; // piles[i]: the minimum ending value of an increasing sequence of length i+1

        for (int i = 0; i < n; ++i) {
            int x = obstacles[i];
            // Find the rightmost pile where x can be placed (non-decreasing, so use upper_bound)
            int idx = upper_bound(piles.begin(), piles.end(), x) - piles.begin();
            if (idx == piles.size()) {
                piles.push_back(x);
            } else {
                piles[idx] = x;
            }
            ans[i] = idx + 1;
        }
        return ans;
    }
};
