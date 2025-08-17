#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    int totalStrength(vector<int>& strength) {
        const int MOD = 1'000'000'007;
        int n = strength.size();

        // 1. Monotonic stack to find left and right bounds for each element
        vector<int> left(n, -1), right(n, n);
        stack<int> st;
        for (int i = 0; i < n; ++i) {
            while (!st.empty() && strength[st.top()] > strength[i])
                right[st.top()] = i, st.pop();
            st.push(i);
        }
        st = stack<int>();
        for (int i = n - 1; i >= 0; --i) {
            while (!st.empty() && strength[st.top()] >= strength[i])
                left[st.top()] = i, st.pop();
            st.push(i);
        }

        // 2. Prefix sums and prefix of prefix sums
        vector<long long> prefix(n + 2, 0), prefix2(n + 2, 0);
        for (int i = 0; i < n; ++i)
            prefix[i + 1] = (prefix[i] + strength[i]) % MOD;
        for (int i = 0; i <= n; ++i)
            prefix2[i + 1] = (prefix2[i] + prefix[i]) % MOD;

        // 3. Contribution calculation
        long long res = 0;
        for (int i = 0; i < n; ++i) {
            int l = left[i], r = right[i];
            int a = i - l, b = r - i;

            long long sumRight = (prefix2[r + 1] - prefix2[i + 1] + MOD) % MOD;
            long long sumLeft = (prefix2[i + 1] - prefix2[l + 1] + MOD) % MOD;

            long long total = (sumRight * a % MOD - sumLeft * b % MOD + MOD) % MOD;
            res = (res + total * strength[i]) % MOD;
        }
        return (int)res;
    }
};
