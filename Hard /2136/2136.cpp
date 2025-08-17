class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        int n = plantTime.size();
        vector<pair<int, int>> seeds(n);
        for (int i = 0; i < n; ++i) seeds[i] = {growTime[i], plantTime[i]};
        sort(seeds.rbegin(), seeds.rend());
        int res = 0, curr = 0;
        for (auto& [g, p] : seeds) {
            curr += p;
            res = max(res, curr + g);
        }
        return res;
    }
};
