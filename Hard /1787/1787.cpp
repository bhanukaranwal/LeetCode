class Solution {
public:
    int minChanges(vector<int>& nums, int k) {
        const int MAXX = 1024;
        vector<int> f(MAXX, 1e9);
        f[0] = 0;
        int n = nums.size();
        for (int i = 0; i < k; ++i) {
            unordered_map<int, int> cnt;
            int size = 0;
            for (int j = i; j < n; j += k) {
                cnt[nums[j]]++;
                size++;
            }
            int minF = *min_element(f.begin(), f.end());
            vector<int> g(MAXX, minF + size);
            for (int x = 0; x < MAXX; ++x) {
                for (auto& [v, c] : cnt) {
                    g[x] = min(g[x], f[x ^ v] + size - c);
                }
            }
            f.swap(g);
        }
        return f[0];
    }
};
