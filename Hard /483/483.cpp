class Solution {
public:
    string smallestGoodBase(string n) {
        long num = stoll(n);
        for (int m = log2(num); m >= 1; --m) {
            long k = pow(num, 1.0 / m);
            long sum = 1, curr = 1;
            for (int i = 0; i < m; ++i) {
                curr *= k;
                sum += curr;
            }
            if (sum == num) return to_string(k);
        }
        return to_string(num - 1);
    }
};
