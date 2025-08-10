class Solution {
public:
    vector<vector<int>> outerTrees(vector<vector<int>>& trees) {
        sort(trees.begin(), trees.end());
        vector<vector<int>> hull;
        auto cross = [](vector<int>& o, vector<int>& a, vector<int>& b) {
            return (a[0] - o[0]) * (b[1] - o[1]) - (a[1] - o[1]) * (b[0] - o[0]);
        };
        for (auto& p : trees) {
            while (hull.size() >= 2 && cross(hull[hull.size()-2], hull[hull.size()-1], p) < 0)
                hull.pop_back();
            hull.push_back(p);
        }
        int lower = hull.size();
        for (int i = trees.size() - 2; i >= 0; --i) {
            while (hull.size() > lower && cross(hull[hull.size()-2], hull[hull.size()-1], trees[i]) < 0)
                hull.pop_back();
            hull.push_back(trees[i]);
        }
        sort(hull.begin(), hull.end());
        hull.erase(unique(hull.begin(), hull.end()), hull.end());
        return hull;
    }
};
