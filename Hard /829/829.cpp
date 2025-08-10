class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int count = 0;
        for (long k = 1; k * (k - 1) / 2 < n; ++k) {
            if ((n - k * (k - 1) / 2) % k == 0) ++count;
        }
        return count;
    }
};
