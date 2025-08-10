class Solution {
public:
    int numDupDigitsAtMostN(int n) {
        return n - countUnique(n);
    }

    int countUnique(int n) {
        vector<int> digits;
        int x = n + 1;
        while (x) {
            digits.push_back(x % 10);
            x /= 10;
        }
        reverse(digits.begin(), digits.end());
        int m = digits.size();
        int res = 0;

        // Count numbers with unique digits and length < m
        for (int i = 1; i < m; ++i) {
            res += 9 * perm(9, i - 1);
        }

        // Count numbers with unique digits and length == m
        set<int> used;
        for (int i = 0; i < m; ++i) {
            for (int d = (i == 0 ? 1 : 0); d < digits[i]; ++d) {
                if (used.count(d)) continue;
                res += perm(9 - i, m - i - 1);
            }
            if (used.count(digits[i])) break;
            used.insert(digits[i]);
        }
        return res;
    }

    int perm(int m, int n) {
        int res = 1;
        for (int i = 0; i < n; ++i) {
            res *= (m - i);
        }
        return res;
    }
};
