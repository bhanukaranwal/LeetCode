class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        int n = flowers.size();
        vector<int> starts, ends;
        for (auto& f : flowers) {
            starts.push_back(f[0]);
            ends.push_back(f[1]);
        }
        sort(starts.begin(), starts.end());
        sort(ends.begin(), ends.end());
        vector<int> res;
        for (int t : people) {
            // Number of flowers started blooming on or before t
            int started = upper_bound(starts.begin(), starts.end(), t) - starts.begin();
            // Number of flowers ended blooming before t (i.e., end < t)
            int ended = lower_bound(ends.begin(), ends.end(), t) - ends.begin();
            res.push_back(started - ended);
        }
        return res;
    }
};
