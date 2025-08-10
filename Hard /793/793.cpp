class Solution {
public:
    int preimageSizeFZF(int k) {
        return count(k + 1) - count(k);
    }
    long count(long k) {
        long l = 0, r = 5L * k + 1;
        while (l < r) {
            long m = l + (r - l) / 2, s = 0, x = m;
            while (x) { s += x / 5; x /= 5; }
            if (s < k) l = m + 1;
            else r = m;
        }
        return l;
    }
};
