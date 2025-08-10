class Solution {
public:
    int maxHappyGroups(int batchSize, vector<int>& groups) {
        vector<int> cnt(batchSize, 0);
        int happy = 0;
        for (int g : groups) {
            int r = g % batchSize;
            if (r == 0) happy++;
            else cnt[r]++;
        }
        unordered_map<long long, int> memo;
        function<int(int, vector<int>&)> dfs = [&](int remain, vector<int>& cnt) {
            long long key = 0;
            for (int i = 1; i < batchSize; ++i) key = key * 31 + cnt[i];
            key = key * batchSize + remain;
            if (memo.count(key)) return memo[key];
            int res = 0;
            for (int i = 1; i < batchSize; ++i) {
                if (cnt[i] == 0) continue;
                cnt[i]--;
                int add = (remain == 0) ? 1 : 0;
                res = max(res, add + dfs((remain + i) % batchSize, cnt));
                cnt[i]++;
            }
            return memo[key] = res;
        };
        return happy + dfs(0, cnt);
    }
};
