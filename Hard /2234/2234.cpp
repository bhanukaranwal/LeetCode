class Solution {
public:
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        int n = flowers.size();
        sort(flowers.begin(), flowers.end());
        for (int& x : flowers) x = min(x, target);
        vector<long long> pre(n + 1, 0);
        for (int i = 0; i < n; ++i) pre[i + 1] = pre[i] + flowers[i];

        // Special case: all gardens are already full
        if (flowers[0] >= target) return 1LL * n * full;

        long long res = 0;
        for (int fullGardens = 0; fullGardens <= n; ++fullGardens) {
            long long rem = newFlowers;
            if (fullGardens > 0) {
                rem -= (long long)target * fullGardens - (pre[n] - pre[n - fullGardens]);
                if (rem < 0) break;
            }
            int left = n - fullGardens;
            long long minPartial = 0;
            if (left > 0) {
                long long lo = 0, hi = target - 1;
                while (lo <= hi) {
                    long long mid = (lo + hi) / 2;
                    int idx = upper_bound(flowers.begin(), flowers.begin() + left, (int)mid) - flowers.begin();
                    long long need = mid * idx - pre[idx];
                    if (need <= rem) {
                        minPartial = mid;
                        lo = mid + 1;
                    } else {
                        hi = mid - 1;
                    }
                }
            }
            // If all gardens are full, do not add partial
            res = max(res, 1LL * fullGardens * full + (left == 0 ? 0 : minPartial * partial));
        }
        return res;
    }
};
