class Solution {
public:
    int largestComponentSize(vector<int>& nums) {
        int n = nums.size();
        int maxNum = *max_element(nums.begin(), nums.end());
        vector<int> parent(maxNum + 1);
        for (int i = 0; i <= maxNum; ++i) parent[i] = i;

        // Union-Find helpers
        function<int(int)> find = [&](int x) {
            if (parent[x] != x) parent[x] = find(parent[x]);
            return parent[x];
        };
        auto unite = [&](int x, int y) {
            parent[find(x)] = find(y);
        };

        // For each number, union it with all its factors > 1
        for (int num : nums) {
            for (int f = 2; f * f <= num; ++f) {
                if (num % f == 0) {
                    unite(num, f);
                    unite(num, num / f);
                }
            }
        }

        unordered_map<int, int> count;
        int res = 0;
        for (int num : nums) {
            int root = find(num);
            res = max(res, ++count[root]);
        }
        return res;
    }
};
