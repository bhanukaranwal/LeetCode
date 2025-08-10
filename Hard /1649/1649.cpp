class Solution {
    static constexpr int MOD = 1e9 + 7;
public:
    int createSortedArray(vector<int>& instructions) {
        int n = instructions.size();
        int maxVal = *max_element(instructions.begin(), instructions.end());
        vector<int> bit(maxVal + 2, 0); // 1-based indexing

        auto update = [&](int i, int delta) {
            while (i < bit.size()) {
                bit[i] += delta;
                i += i & -i;
            }
        };

        auto query = [&](int i) {
            int res = 0;
            while (i > 0) {
                res += bit[i];
                i -= i & -i;
            }
            return res;
        };

        long long cost = 0;
        for (int i = 0; i < n; ++i) {
            int x = instructions[i];
            int less = query(x - 1);
            int greater = i - query(x);
            cost = (cost + min(less, greater)) % MOD;
            update(x, 1);
        }
        return cost;
    }
};
