class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        int n = target.size();
        int N = 1 << n; // total states
        vector<vector<int>> stickerCount;
        for (auto& s : stickers) {
            vector<int> cnt(26, 0);
            for (char c : s) cnt[c - 'a']++;
            stickerCount.push_back(cnt);
        }
        unordered_map<int, int> memo;
        memo[0] = 0; // base: no letters needed

        function<int(int)> dp = [&](int mask) -> int {
            if (memo.count(mask)) return memo[mask];
            int res = INT_MAX;
            // Try every sticker
            for (auto& cnt : stickerCount) {
                // Optimization: skip stickers not containing any needed letter
                bool useful = false;
                for (int i = 0; i < n; ++i) {
                    if ((mask >> i) & 1) {
                        if (cnt[target[i] - 'a'] > 0) {
                            useful = true;
                            break;
                        }
                    }
                }
                if (!useful) continue;

                vector<int> cnt2 = cnt;
                int next_mask = mask;
                for (int i = 0; i < n; ++i) {
                    if ((mask >> i) & 1 && cnt2[target[i] - 'a'] > 0) {
                        cnt2[target[i] - 'a']--;
                        next_mask ^= (1 << i);
                    }
                }
                int tmp = dp(next_mask);
                if (tmp != -1)
                    res = min(res, 1 + tmp);
            }
            memo[mask] = (res == INT_MAX ? -1 : res);
            return memo[mask];
        };

        int full_mask = (1 << n) - 1;
        return dp(full_mask);
    }
};
